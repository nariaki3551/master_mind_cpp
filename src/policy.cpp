#include <algorithm>
#include <omp.h>
#include "policy.h"


namespace MasterMind
{


std::mt19937 engine = std::mt19937(0);


Code randomPolicy(
      CodePtrList &S,
      CodePtrList &G
      ) noexcept
{
   // random sampling from G
   std::uniform_int_distribution<> sampler(0, G.size()-1);
   Code guess = Code(*G[sampler(engine)]);
   return guess;
}


double minmax(
      std::map<Hint, int> &d,
      int N
      ) noexcept
{
   double maxElm = -1;
   for ( auto pair : d )
   {
      if ( pair.second > maxElm ) maxElm = pair.second;
   }
   return maxElm;
}


double expMinmax(
      std::map<Hint, int> &d,
      int N
      ) noexcept
{
   double exp = 0;
   for ( auto pair : d )
   {
      exp += pair.second * pair.second;
   }
   return exp / N;
}


double entropy(
      std::map<Hint, int> &d,
      int N
      ) noexcept
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


template<class ObjFunc>
Code distPolicy(
      CodePtrList &S,
      CodePtrList &G,
      ObjFunc objFunc,
      Config &config
      ) noexcept
{
   std::vector<double> objs(G.size());
   std::map<Hint, int> d;  // distribution
   Hint hint;
#pragma omp parallel for private(hint) firstprivate(d)
   for ( int i = 0; i < static_cast<int>(G.size()); ++i )
   {
      auto code = G[i];
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
      objs[i] = objFunc(d, S.size());
   }

   auto iter = std::min_element(objs.begin(), objs.end());
   int index = std::distance(objs.begin(), iter);
   Code guess(*G[index]);
   return guess;
}


Code policy(
      CodePtrList &S,
      CodePtrList &G,
      Config &config
      ) noexcept
{
   if ( config.policy == "random" )
   {
      return randomPolicy(S, G);
   }
   else if ( config.policy == "minmax" )
   {
      return distPolicy(S, G, minmax, config);
   }
   else if ( config.policy == "exp_minmax" )
   {
      return distPolicy(S, G, expMinmax, config);
   }
   else if ( config.policy == "entropy" )
   {
      return distPolicy(S, G, entropy, config);
   }
   else
   {
      exit(1);
   }
}


}; // MasterMind
