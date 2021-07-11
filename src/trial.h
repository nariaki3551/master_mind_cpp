#ifndef __TRIAL_H__
#define __TRIAL_H__

#include <algorithm>

#include "def.h"
#include "config.h"
#include "utils.h"


namespace MasterMind
{

/**
* @fn Code trial(CodePtrList &S, Code &guess, Config &config)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in, out] S 秘密コードの候補集合
* @param[in] guess 推論コード
* @param[in] config パラメタ
*/
void trial(
      CodePtrList &S,
      CodePtr guess,
      Config &config
      ) noexcept;


}; // MasterMind


#endif   //__TRIAL_H__
