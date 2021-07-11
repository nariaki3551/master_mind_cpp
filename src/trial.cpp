#include "trial.h"


namespace MasterMind
{


void trial(
      CodePtrList &S,
      CodePtr guess,
      Config &config
      ) noexcept
{
   // 推論コードの表示
   if ( config.interactive )
   {
      std::cout << "guess is " << strCode(guess) << std::endl;
   }

   Hint InputHint;
   if ( config.interactive )
   {
      // 入力待ち
      int hit, blow;
      std::cout << " input hit blow (e.g. 2 2): ";
      std::cin >> hit >> blow;
      InputHint = Hint(hit, blow);
   }
   else
   {
      // config.secretから正解
      InputHint = countHitBlow(
            config.secret, guess, config
            );
   }

   // 選別
   CodePtrList newS;
   for ( auto &code : S )
   {
      if( countHitBlow(code, guess, config) == InputHint )
      {
         newS.push_back(code);
      }
   }
   S = newS;
}


}; // MasterMind
