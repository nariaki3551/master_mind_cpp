#ifndef __POLICY_H__
#define __POLICY_H__

#include <random>
#include <cmath>
#include <map>
#include <unordered_map>

#include "def.h"
#include "utils.h"


namespace MasterMind
{


/**
 * @var engine
 * @brief random policy用
 */
extern std::mt19937 engine;


/**
* @fn CodePtr randomPolicy(CodePtrList S, CodePtrList G)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in] S 秘密コードの候補集合
* @param[in] G 推論コードの候補集合
* @return 推論コード
*/
CodePtr randomPolicy(
      CodePtrList &S,
      CodePtrList &G
      ) noexcept;


/**
 * @fn minmax(std::map<Hint, int> &d, int N)
 * @brief score function based on minmax policy
 * @param[in] d distribution of S by test code
 * @param[in] N size of S
 * @return the smaller the better score value
 */
double minmax(
      std::map<Hint, int> &d,
      int N
      ) noexcept;


/**
 * @fn expMinMax(std::map<Hint, int> &d, int N)
 * @brief score function based on expMinMax policy
 * @param[in] d distribution of S by test code
 * @param[in] N size of S
 * @return the smaller the better score value
 */
double expMinmax(
      std::map<Hint, int> &d,
      int N
      ) noexcept;


/**
 * @fn entropy(std::map<Hint, int> &d, int N)
 * @brief score function based on entropy policy
 * @param[in] d distribution of S by test code
 * @param[in] N size of S
 * @return the smaller the better score value
 */
double entropy(
      std::map<Hint, int> &d,
      int N
      ) noexcept;


/**
* @fn CodePtr minmaxPolicy(CodePtrList &S, CodePtrList &G, Config &config)
* @brief 推論コード候補集合Gから, objFuncの値が最小のものを選択する
* @param[in] S 秘密コードの候補集合
* @param[in] G 推論コードの候補集合
* @param[in] objFunc 推論コード取得用のスコア関数
* @param[in] config パラメタ
* @return 推論コード
*/
template<class ObjFunc>
CodePtr distPolicy(
      CodePtrList &S,
      CodePtrList &G,
      ObjFunc objFunc,
      Config &config
      ) noexcept;


/**
* @fn CodePtr policy(CodePtrList S, CodePtrList G, Config &config)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in] S 秘密コードの候補集合
* @param[in] G 推論コードの候補集合
* @param[in] config パラメタ
* @return 推論コード
*/
CodePtr policy(
      CodePtrList &S,
      CodePtrList &G,
      Config &config
      ) noexcept;


}  // MasterMind


#endif   // __POLICY_H__
