#ifndef __DEF_H__
#define __DEF_H__

#include <iostream>
#include <deque>
#include <vector>


/*
 * データ型
 */
using ColorType   = short;
using HintType    = short;
using Code        = std::vector<ColorType>;
using CodePtr     = Code *;
using HitBlow     = std::pair<HintType, HintType>;
using CodeList    = std::deque<Code>;
using CodePtrList = std::deque<CodePtr>;


#endif // __DEF_H__
