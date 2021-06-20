#ifndef __UTILS_H__
#define __UTILS_H__

#include <sstream>
#include <memory>
#include <vector>

#include "def.h"
#include "config.h"


namespace MasterMind
{

/**
* @fn std::string showCode(Code code)
* @brief コードを表示する
* @param[in] code コード
* @return コードのstring
*/
inline
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


/**
* @fn std::string showCode(Code code)
* @brief コードを表示する
* @param[in] code コード
* @return コードのstring
*/
inline
std::string strCode(
      CodePtr code
      ) noexcept
{
   return strCode(*code);
}


std::vector<int> x(1, 0);
std::vector<int> y(1, 0);
/**
* @fn Hint countHitBlow(Code &code, Code &guess)
* @brief コード2つから, hit, blowを計算する
* @param[in] code コード
* @param[in] guess コード
* @param[in] config パラメタ
* @return (hit, blow)
*/
inline
auto countHitBlow(
      Code &code,
      Code &guess,
      Config &config
      ) noexcept
{
   if ( x.size() < static_cast<decltype(x.size())>(config.nColors) )
   {
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
   return Hint(hit, blow);
}


/**
* @fn CodePtrList code(CodePtrList &codePtrList)
* @brief copi CodePtrList
* @param[in] codePtrList
* @return copied codePtrList
*/
inline
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


#endif   // __UTILS_H__
