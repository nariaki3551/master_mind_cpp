#ifndef __RUN_H__
#define __RUN_H__

#include <iostream>

#include "def.h"
#include "config.h"
#include "utils.h"
#include "policy.h"
#include "trial.h"
#include "codeGenerator.h"



namespace MasterMind
{

/**
 * @fn void runInteractive(Config &config)
 * @brief ユーザの(hit, blow)入力による探索
 * @param[in] config
 */
void runInteractive(
      Config &config
      ) noexcept;



/**
 * @fn void runInteractive(Config &config)
 * @brief 全てのsecret codeに対する計測
 * @param[in] config
 */
void runTest(
      Config &config
      ) noexcept;


/**
* @fn Config getConfig(int argc, char *argv[])
* @brief コマンドライン入力を受けとる
* @param[in] argc
* @param[in] argv
* @return Config パラメタ管理クラス
*/
Config getConfig(
      int argc,
      char *argv[]
      );


}; // MasterMind


#endif   // __RUN_H__
