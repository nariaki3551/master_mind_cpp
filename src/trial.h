#ifndef __TRIAL_H__
#define __TRIAL_H__

#include <algorithm>

#include "def.h"
#include "utils.h"


/**
* @fn Code trial(CodeList &S, Code &guess)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in, out] S 秘密コードの候補集合
* @param[in] 推論コード
*/
auto trial(
      CodeList &S,
      Code &guess
      )
{
   // 入力待ち
   int hit, blow;
   std::cout << "guess is " << strCode(guess) << std::endl;
   std::cout << " input hit blow (e.g. 2 2): ";
   std::cin >> hit >> blow;
   HitBlow InputHitBlow(hit, blow);

   // 選別
   CodeList newS;
   for ( auto code : S )
   {
      if( countHitBlow(code, guess) == InputHitBlow )
      {
         newS.push_back(code);
      }
   }
   S = newS;
}


#endif   //__TRIAL_H__
