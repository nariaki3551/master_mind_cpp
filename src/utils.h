#ifndef __UTILS_H__
#define __UTILS_H__

#include <sstream>
#include <memory>
#include <vector>
#include <map>

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
std::string strCode(
      Code &code
      ) noexcept;


/**
* @fn std::string showCode(Code code)
* @brief コードを表示する
* @param[in] code コード
* @return コードのstring
*/
std::string strCode(
      CodePtr code
      ) noexcept;


extern thread_local LruCacheOfCountHitBlow lruCacheOfCountHitBlow;
extern thread_local std::vector<int> x;
extern thread_local std::vector<int> y;
/**
* @fn Hint countHitBlow(CodePtr code, CodePtr guess)
* @brief コード2つから, hit, blowを計算する
* @param[in] code コード
* @param[in] guess コード
* @param[in] config パラメタ
* @return (hit, blow)
*/
Hint countHitBlow(
      CodePtr code,
      CodePtr guess,
      Config &config
      ) noexcept;


/**
* @fn CodePtrList copy(CodePtrList &codePtrList)
* @brief copi CodePtrList
* @param[in] codePtrList
* @return copied codePtrList
*/
CodePtrList copy(
      CodePtrList &codePtrList
      ) noexcept;


}; // MasterMind


#endif   // __UTILS_H__
