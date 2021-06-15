#include <iostream>
#include <sstream>
#include <deque>
#include <vector>
#include <algorithm>
#include <random>

#include "def.h"
#include "utils.h"
#include "policy.h"
#include "trial.h"


int main()
{
   // とりあえず(2色, 2ピン)
   CodeList S{ Code{0,0}, Code{0,1}, Code{1,0}, Code{1,1} };

   // main
   decltype(policy(S, S)) guess;
   while( S.size() > 1 )
   {
      guess = policy(S, S);   // G <- S
      trial(S, guess);        // update S
   }

   // post process
   auto secret = S[0];
   std::cout << "secret is " << strCode(secret) << std::endl;

   return 0;
}
