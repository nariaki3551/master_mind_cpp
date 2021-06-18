#ifndef __DEF_H__
#define __DEF_H__

#include <iostream>
#include <deque>
#include <vector>


/*
 * データ型
 */
using ColorType   = int;
using HintType    = int;
using Code        = std::vector<ColorType>;
using HitBlow     = std::pair<HintType, HintType>;
using CodeList    = std::deque<Code>;


#endif // __DEF_H__
