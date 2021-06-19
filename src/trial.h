#ifndef __TRIAL_H__
#define __TRIAL_H__

#include <algorithm>

#include "def.h"
#include "config.h"
#include "utils.h"


namespace MasterMind
{

/**
* @fn Code trial(CodePtrList &S, Code &guess, Config &config)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in, out] S 秘密コードの候補集合
* @param[in] guess 推論コード
* @param[in] config パラメタ
*/
inline
auto trial(
      CodePtrList &S,
      Code &guess,
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
      InputHint = countHitBlow(config.secret, guess, config);
   }

   // 選別
   CodePtrList newS;
   for ( auto code : S )
   {
      if( countHitBlow(*code, guess, config) == InputHint )
      {
         newS.push_back(code);
      }
   }
   S = newS;
}

}; // MasterMind


#endif   //__TRIAL_H__
