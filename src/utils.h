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
 * パラメータ管理
 */
class Config
{
   public:
      int nColors;      // number of colors
      int nPins;        // number of pins
      bool duplicate;   // if it is true, then color-duplication is allowed

      /**
      * @brief Constructor
      * @param[in] inNColors 色数
      * @param[in] inNPins ピン数
      * @param[in] inDuplicate 色の重複を許すかどうか
      */
      Config(
            int inNColors,
            int inNPins,
            bool inDuplicate
            )
         :
            nColors(inNColors),
            nPins(inNPins),
            duplicate(inDuplicate)
      {}

      /**
      * @brief 管理情報をstringにする
      * @return std::string
      */
      std::string str()
      {
         std::ostringstream os;
         os << "Config:" << std::endl;
         os << "  nColors: " << nColors << std::endl;
         os << "  nPins: " << nPins << std::endl;
         os << "  duplicate: " << duplicate << std::endl;
         return os.str();
      }
};


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
