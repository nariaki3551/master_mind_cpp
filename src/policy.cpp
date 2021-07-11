#include <algorithm>
#include <omp.h>
#include "policy.h"
#include <progresscpp/ProgressBar.hpp>


namespace MasterMind
{


std::mt19937 engine = std::mt19937(0);


CodePtr randomPolicy(
      CodePtrList &S,
      CodePtrList &G
      ) noexcept
{
   // random sampling from G
   std::uniform_int_distribution<> sampler(0, G.size()-1);
   return G[sampler(engine)];
}


double minmax(
      std::map<Hint, int> &d,
      int N
      ) noexcept
{
   double maxElm = -1;
   for ( auto &pair : d )
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
   for ( auto &pair : d )
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
   double minus_entropy = 0.0;
   double p = 0.0;
   for ( auto &pair : d )
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
CodePtr distPolicy(
      CodePtrList &S,
      CodePtrList &G,
      ObjFunc objFunc,
      Config &config
      ) noexcept
{
   std::vector<double> objs(G.size());
   std::map<Hint, int> d;  // distribution
   Hint hint;

   // initialize the bar
   progresscpp::ProgressBar progressBar(G.size(), 70);

#pragma omp parallel for private (hint, d) if (!omp_in_parallel())
   for ( int i = 0; i < static_cast<int>(G.size()); ++i )
   {
#pragma omp critical
      if ( config.interactive )
      {
         // record the tick and display the bar
         ++progressBar;
         progressBar.display();
      }
      auto code = G[i];
      d.clear();
      for ( auto &_code : S )
      {
         hint = countHitBlow(code, _code, config);
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
   return G[index];
}


CodePtr policy(
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
