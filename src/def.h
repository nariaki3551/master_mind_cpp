#ifndef __DEF_H__
#define __DEF_H__

#include <iostream>
#include <memory>
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

};  // MasterMind


#endif // __DEF_H__
