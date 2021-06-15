#include <iostream>
#include <sstream>
#include <deque>
#include <vector>
#include <algorithm>
#include <random>

/*
 * データ型
 */
typedef std::vector<int>      Code;
typedef std::pair<int, int>   HitBlow;
typedef std::deque<Code>      CodeList;


/**
* @fn HitBlow countHitBlow(Code &code, Code &guess)
* @brief コード2つから, hit, blowを計算する
* @param[in] code コード
* @param[in] guess コード
* @return (hit, blow)
*/
auto countHitBlow(
      Code &code,
      Code &guess
      )
{
    std::vector<int> x(2, 0);
    std::vector<int> y(2, 0);
    int hit = 0, blow = 0;
    for( int i = 0; i < 2; i++ )
    {
       if( code[i] == guess[i] )
       {
          hit++;
       }
       else
       {
          x[code[i]]++;
          y[guess[i]]++;
       }
    }
    for( int i = 0; i < 2; i++ )
    {
       blow += std::min(x[i], y[i]);
    }
    return HitBlow(hit, blow);
}


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
   std::cout << "guess is [ " << guess[0] << " " << guess[1] << " ]" << std::endl;
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



/**
* @fn Code policy(CodeList S, CodeList G)
* @brief 推論コード候補集合Gから1つを選択する
* @param[in] S 秘密コードの候補集合
* @param[in] G 推論コードの候補集合
* @return 推論コード
*/
auto policy(
      CodeList &S,
      CodeList &G
      )
{
   // random sampling from G
   std::mt19937 engine(0);
   std::uniform_int_distribution<> sampler(0, G.size()-1);
   auto guess = G[sampler(engine)];
   return guess;
}


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
   std::cout << "guess is [ " << secret[0] << " " << secret[1] << " ]" << std::endl;

   return 0;
}
