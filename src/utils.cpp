#include "utils.h"


namespace MasterMind
{


std::string strCode(
      Code &code
      ) noexcept
{
   std::ostringstream os;
   os << "[";
   for ( int pin : code )
   {
      os << " " << pin;
   }
   os << " ]";
   return os.str();
}


std::string strCode(
      CodePtr code
      ) noexcept
{
   return strCode(*code);
}


thread_local std::map<CodePair, Hint> lruCacheOfCountHitBlow;
thread_local std::vector<int> x(0, 0);
thread_local std::vector<int> y(0, 0);
Hint countHitBlow(
      Code &code,
      Code &guess,
      Config &config
      ) noexcept
{
   CodePair codePair;
   if ( code < guess )
      codePair = std::make_pair(code, guess);
   else
      codePair = std::make_pair(guess, code);
   auto itr = lruCacheOfCountHitBlow.find(codePair);
   if ( itr != lruCacheOfCountHitBlow.end() )
      return lruCacheOfCountHitBlow.at(codePair);

   if ( static_cast<int>(x.size()) < config.nColors )
   {
      x.clear(); y.clear();
      x.resize(config.nColors);
      y.resize(config.nColors);
   }
   std::fill(x.begin(), x.end(), 0);
   std::fill(y.begin(), y.end(), 0);
   int hit = 0, blow = 0;
   for( int i = 0; i < config.nPins; ++i )
   {
      if( code[i] == guess[i] )
      {
         hit++;
      }
      else
      {
         x[code[i]]++;
         y[guess[i]]++;
      }
   }
   for( int i = 0; i < config.nColors; ++i )
   {
      blow += std::min(x[i], y[i]);
   }

   Hint hint{hit, blow};
   lruCacheOfCountHitBlow.emplace(codePair, hint);
   return hint;
}


CodePtrList copy(
      CodePtrList &codePtrList
      ) noexcept
{
   CodePtrList _codePtrList;
   for ( auto code : codePtrList )
   {
      _codePtrList.push_back(std::make_shared<Code>(Code(*code)));
   }
   return _codePtrList;
}


}; // MasterMind
