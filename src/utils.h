#ifndef __UTILS_H__
#define __UTILS_H__

#include <sstream>
#include <vector>

#include "def.h"


/**
* @fn std::string showCode(Code code)
* @brief コードを表示する
* @param[in] code コード
* @return コードのstring
*/
std::string strCode(
      Code code
      )
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
* @fn HitBlow countHitBlow(Code &code, Code &guess)
* @brief コード2つから, hit, blowを計算する
* @param[in] code コード
* @param[in] guess コード
* @return (hit, blow)
*/
auto countHitBlow(
      Code &code,
      Code &guess
      )
{
    std::vector<int> x(2, 0);
    std::vector<int> y(2, 0);
    int hit = 0, blow = 0;
    for( int i = 0; i < 2; i++ )
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
    for( int i = 0; i < 2; i++ )
    {
       blow += std::min(x[i], y[i]);
    }
    return HitBlow(hit, blow);
}


#endif   // __UTILS_H__
