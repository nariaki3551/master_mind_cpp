#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__

#include <cassert>
#include <set>

#include "def.h"
#include "utils.h"
#include "itertools.h"

namespace MasterMind
{

/**
* @fn CodePtrList allCodeGenerator(Config &config, CodePtrList &codePtrList)
* @brief 全てのコード配列を列挙する.
* @param[in] config パラメタ
* @param[out] codePtrList コード配列
*/
void allCodeGenerator(
      Config &config,
      CodePtrList &codePtrList
      ) noexcept;


/**
 * @fn void setGuessCandidates(CodePtrList &codePtrList, CodeList &guessHist,
 *             Config &config,CodePtrList &guessCandidates)
 * @brief 推測コード集合を計算する
 * @param[in] codePtrList コード集合
 * @param[in] guessHist 推測履歴
 * @param[in] config パラメタ
 * @param[out] guessCandidates 推測コード集合
 * @details まだ推測に使用されていない色についての区別は行わない
 */
void setGuessCandidates(
      CodePtrList &codePtrList,
      CodeList &guessHist,
      Config &config,
      CodePtrList &guessCandidates
      ) noexcept;


}; // MasterMind


#endif // __CODE_GENERATOR_H__
