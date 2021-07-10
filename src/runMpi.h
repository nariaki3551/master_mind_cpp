#ifndef __RUN_MPI_H__
#define __RUN_MPI_H__

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
 * @brief 全てのsecret codeに対する計測
 * @param[in] config
 * @param[in] nProcesses size of MPI
 * @param[in] rank rank of MPI
 */
void runTestPara(
      Config &config,
      int nProcesses,
      int rank
      ) noexcept;

}; // MasterMind


#endif   // __RUN_MPI_H__
