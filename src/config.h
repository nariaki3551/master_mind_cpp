#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <sstream>
#include "def.h"


namespace MasterMind
{

/**
 * パラメータ管理
 */
class Config
{
   public:
      int nColors;            // number of colors
      int nPins;              // number of pins
      bool duplicate;         // if it is true, then color-duplication is allowed
      bool interactive;       // if it is true, then test by user input
      std::string policy;     // policy
      CodePtr secret;         // for test

      /**
      * @brief Constructor
      * @param[in] inNColors 色数
      * @param[in] inNPins ピン数
      * @param[in] inDuplicate 色の重複を許すかどうか
      */
      Config(
            int inNColors,
            int inNPins,
            bool inDuplicate,
            bool inInteractive=true,
            std::string inPolicy="random"
            )
         :
            nColors(inNColors),
            nPins(inNPins),
            duplicate(inDuplicate),
            interactive(inInteractive),
            policy(inPolicy)
      {}


      /**
       * @brief setter of secret
       * @param[in] code コード
       */
      void setSecret(
            CodePtr code
            )
      {
         secret = code;
      }


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
         os << "  policy: " << policy << std::endl;
         return os.str();
      }
};

}; // MasterMind


#endif   // __CONFIG_H__
