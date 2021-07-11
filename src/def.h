#ifndef __DEF_H__
#define __DEF_H__

#include <iostream>
#include <memory>
#include <map>
#include <unordered_map>
#include <deque>
#include <vector>


namespace MasterMind
{

/*
 * データ型
 */
using ColorType   = short;
using HintType    = short;
using Code        = std::vector<ColorType>;
using CodePtr     = std::shared_ptr<Code>;
using Hint        = std::pair<HintType, HintType>;
using CodeList    = std::deque<Code>;
using CodePtrList = std::deque<CodePtr>;
using CodePtrPair = std::pair<CodePtr, CodePtr>;
using CodePair    = std::pair<Code, Code>;


/**
* @fn CodePtr createPtr(Code code)
* @briefcreate CodePtr from Code
* @param[in] code
* @return CodePtr
*/
inline
CodePtr createPtr(
      Code code
      )
{
   return std::make_shared<Code>(code);
}


class CompareCodePtr
{
public:
   bool operator()(
         const CodePtrPair &left,
         const CodePtrPair &right
         ) const
   {
      return ( ( *(left.first) < *(right.first) )
            || ( *(left.first) == *(right.first) && *(left.second) < *(right.second)) );
   }
};

using LruCacheOfCountHitBlow = std::map<CodePtrPair, Hint, CompareCodePtr>;
// using LruCacheOfCountHitBlow = std::unordered_map<CodePtrPair, Hint, CompareCodePtr>;
// using LruCacheOfCountHitBlow = std::map<CodePtrPair, Hint>;


};  // MasterMind


#endif // __DEF_H__
