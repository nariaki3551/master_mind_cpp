#include "utils.h"


namespace MasterMind
{


std::string strCode(
      Code &code
      ) noexcept
{
   std::ostringstream os;
   os << "[";
   for ( auto &pin : code )
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


thread_local LruCacheOfCountHitBlow lruCacheOfCountHitBlow;
thread_local std::vector<int> x(0, 0);
thread_local std::vector<int> y(0, 0);
Hint countHitBlow(
      CodePtr code,
      CodePtr guess,
      Config &config
      ) noexcept
{
#if USE_LRU_CACHE
   CodePtrPair codePair;
   if ( code < guess )
      codePair = std::make_pair(code, guess);
   else
      codePair = std::make_pair(guess, code);
   auto itr = lruCacheOfCountHitBlow.find(codePair);
   if ( itr != lruCacheOfCountHitBlow.end() )
      return lruCacheOfCountHitBlow.at(codePair);
#endif

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
      if( code->at(i) == guess->at(i) )
      {
         hit++;
      }
      else
      {
         x[code->at(i)]++;
         y[guess->at(i)]++;
      }
   }
   for( int i = 0; i < config.nColors; ++i )
   {
      blow += std::min(x[i], y[i]);
   }

   Hint hint{hit, blow};
#if USE_LRU_CACHE
   lruCacheOfCountHitBlow.emplace(codePair, hint);
#endif
   return hint;
}


CodePtrList copy(
      CodePtrList &codePtrList
      ) noexcept
{
   CodePtrList _codePtrList;
   for ( auto &code : codePtrList )
   {
      _codePtrList.push_back(createPtr(Code(*code)));
   }
   return _codePtrList;
}


}; // MasterMind
