#ifndef __TRIAL_H__
#define __TRIAL_H__

#include <algorithm>

#include "def.h"
#include "utils.h"


/**
* @fn Code trial(CodePtrList &S, Code &guess, Config &config)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in, out] S 秘密コードの候補集合
* @param[in] guess 推論コード
* @param[in] config パラメタ
*/
auto trial(
      CodePtrList &S,
      Code &guess,
      Config &config
      )
{
   // 推論コードの表示
   if ( config.interactive )
   {
      std::cout << "guess is " << strCode(guess) << std::endl;
   }

   HitBlow InputHitBlow;
   if ( config.interactive )
   {
      // 入力待ち
      int hit, blow;
      std::cout << " input hit blow (e.g. 2 2): ";
      std::cin >> hit >> blow;
      InputHitBlow = HitBlow(hit, blow);
   }
   else
   {
      // config.secretから正解
      InputHitBlow = countHitBlow(config.secret, guess, config);
   }

   // 選別
   CodePtrList newS;
   for ( auto code : S )
   {
      if( countHitBlow(*code, guess, config) == InputHitBlow )
      {
         newS.push_back(code);
      }
   }
   S = newS;
}


#endif   //__TRIAL_H__
