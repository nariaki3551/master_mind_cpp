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
* @fn Code randomPolicy(CodePtrList S, CodePtrList G)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in] S 秘密コードの候補集合
* @param[in] G 推論コードの候補集合
* @return 推論コード
*/
auto randomPolicy(
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
      )
{
   double maxElm = -1;
   for ( auto pair : d )
   {
      if ( pair.second > maxElm ) maxElm = pair.second;
   }
   return maxElm;
}


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
      )
{
   double exp = 0;
   for ( auto pair : d )
   {
      exp += pair.second * pair.second;
   }
   return exp / N;
}


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
      )
{
   double minus_entropy = 0;
   double p;
   for ( auto pair : d )
   {
      if ( pair.second > 0 )
      {
         p = static_cast<double>(pair.second) / N;
         minus_entropy += p * std::log(p);
      }
   }
   return minus_entropy;
}


/**
* @fn Code minmaxPolicy(CodePtrList &S, CodePtrList &G, Config &config)
* @brief 推論コード候補集合Gから, 施行後の最悪時の候補数が最小のものを選択する
* @param[in] S 秘密コードの候補集合
* @param[in] G 推論コードの候補集合
* @param[in] config パラメタ
* @return 推論コード
*/
template<class ObjFunc>
auto distPolicy(
      CodePtrList &S,
      CodePtrList &G,
      ObjFunc objFunc,
      Config &config
      )
{
   Code guess;
   double best, objValue;
   bool first = true;
   std::map<Hint, int> d;  // distribution
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
      objValue = objFunc(d, S.size());
      if ( first || objValue < best )
      {
         best = objValue;
         guess = Code(*code);
         first = false;
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
      )
{
   if ( config.policyType == "random" )
   {
      return randomPolicy(S, G);
   }
   else if ( config.policyType == "minmax" )
   {
      return distPolicy(S, G, minmax, config);
   }
   else if ( config.policyType == "exp_minmax" )
   {
      return distPolicy(S, G, expMinmax, config);
   }
   else if ( config.policyType == "entropy" )
   {
      return distPolicy(S, G, entropy, config);
   }
   else
   {
      exit(1);
   }
}


}  // MasterMind


#endif   // __POLICY_H__
