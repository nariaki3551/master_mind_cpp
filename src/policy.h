#ifndef __POLICY_H__
#define __POLICY_H__

#include <random>
#include <map>
#include <unordered_map>

#include "def.h"
#include "utils.h"


namespace MasterMind
{


/**
* @fn Code randomPolicy(CodePtrList S, CodePtrList G)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in] S 秘密コードの候補集合
* @param[in] G 推論コードの候補集合
* @return 推論コード
*/
auto randomPolicy(
      CodePtrList &S,
      CodePtrList &G
      ) noexcept
{
   // random sampling from G
   std::mt19937 engine(0);
   std::uniform_int_distribution<> sampler(0, G.size()-1);
   Code guess = Code(*G[sampler(engine)]);
   return guess;
}


/**
* @fn Code minmaxPolicy(CodePtrList S, CodePtrList G)
* @brief 推論コード候補集合Gから, 施行後の最悪時の候補数が最小のものを選択する
* @param[in] S 秘密コードの候補集合
* @param[in] G 推論コードの候補集合
* @return 推論コード
*/
auto minmaxPolicy(
      CodePtrList &S,
      CodePtrList &G,
      Config &config
      ) noexcept
{
   Code guess;
   int bestScore = S.size();
   std::map< Hint, int > d;  // distribution
   Hint hint;
   for ( auto code : G )
   {
      d.clear();
      for ( auto _code : S )
      {
         hint = countHitBlow(*code, *_code, config);
         if ( d.find(hint) == d.end() )
         {
            d.emplace(hint, 0);
         }
         d.at(hint)++;
      }
      int maxElm = 0;
      for ( auto pair : d )
      {
         maxElm = std::max(pair.second, maxElm);
      }
      if ( maxElm < bestScore )
      {
         guess = Code(*code);
         bestScore = maxElm;
      }
   }
   return guess;
}


/**
* @fn Code policy(CodePtrList S, CodePtrList G, Config &config)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in] S 秘密コードの候補集合
* @param[in] G 推論コードの候補集合
* @param[in] config パラメタ
* @return 推論コード
*/
auto policy(
      CodePtrList &S,
      CodePtrList &G,
      Config &config
      ) noexcept
{
   if ( config.policyType == "random" )
   {
      return randomPolicy(S, G);
   }
   else if ( config.policyType == "minmax" )
   {
      return minmaxPolicy(S, G, config);
   }
   else
   {
      exit(1);
   }
}


}  // MasterMind


#endif   // __POLICY_H__
