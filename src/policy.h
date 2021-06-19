#ifndef __POLICY_H__
#define __POLICY_H__

#include <random>

#include "def.h"


namespace MasterMind
{

/**
* @fn Code policy(CodePtrList S, CodePtrList G)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in] S 秘密コードの候補集合
* @param[in] G 推論コードの候補集合
* @return 推論コード
*/
auto policy(
      CodePtrList &S,
      CodePtrList &G
      )
{
   // random sampling from G
   std::mt19937 engine(0);
   std::uniform_int_distribution<> sampler(0, G.size()-1);
   Code guess = Code(*G[sampler(engine)]);
   return guess;
}

}  // MasterMind


#endif   // __POLICY_H__
