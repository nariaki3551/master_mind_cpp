#ifndef __ITERTOOLS_H__
#define __ITERTOOLS_H__

#include <memory>
#include <cmath>
#include "def.h"


namespace MasterMind
{

/**
 * @brief iterator管理用
 */
class Itertools
{
public:
   /**
    * @brief beginからendまでstep幅のvecorを返す
    * @tparam T returned value type
    * @param[in] begin
    * @param[in] end
    * @param[in] step default is 1
    * @retrun vecor<T>
    * @details range(0, 5) --> {0, 1, 2, 3, 4}
    *          range(5, -1, -1) --> {5, 4, 3, 2, 1}
    */
   template<typename T=int>
   std::vector<T> range(
         int begin,
         int end,
         int step=1
         ) noexcept
   {
      assert( ( (end - begin)*step >= 0) && step != 0 );   // (end >= begin) => step > 0 && ...
      int n = std::abs(round((begin - end) / step));
      std::vector<T> res(n);
      res[0] = begin;
      for ( int i = 1; i < n; i++ ) res[i] = res[i-1] + step;
      return res;
   }


   /**
    * @brief 長さrのpool要素の直積
    * @parma[in] pool 要素配列
    * @param[in] r 長さ
    * @param[in] codePtrList コード保存用
    * @details product({0,1}, 3) --> 000 001 010 011 100 101 110 111
    */
   void product(
         std::vector<ColorType> pool,
         int r,
         CodePtrList &codePtrList
         ) noexcept
   {
      assert( codePtrList.size() == 0 );
      for ( auto i : pool )
      {
         codePtrList.push_back(std::make_shared<Code>(Code{i}));
      }
      int n = 1;
      for ( int i = 0; i < (r-1); i++ )
      {
         n *= pool.size();
         for ( int j = 0; j < n; j++ )
         {
            CodePtr code = codePtrList.front();
            codePtrList.pop_front();
            for ( auto k : pool )
            {
               CodePtr newCode = std::make_shared<Code>(Code(*code));
               newCode->push_back(k);
               codePtrList.push_back(newCode);
            }
         }
      }
   }


   /**
    * @brief 長さrのpool要素の順列
    * @param[in] pool 要素配列
    * @param[in] r 長さ
    * @param[out] codePtrList コード保存用
    * @details permutations({0,1,2,3}, 2) --> 01 02 03 12 13 23
    */
   void permutations(
         std::vector<ColorType> pool,
         int r,
         CodePtrList &codePtrList
         ) noexcept
   {
      assert( static_cast<decltype(pool.size())>(r) <= pool.size() );
      assert( codePtrList.size() == 0 );
      Code code(r);
      int n = pool.size();
      auto indices = range(0, n);
      auto cycles = range(n, n-r, -1);
      for ( int k = 0; k < r; k++ ) code[k] = pool[indices[k]];
      codePtrList.push_back(std::make_shared<Code>(Code(code)));

      bool finish = false;
      while ( !finish )
      {
         finish = true;
         for ( auto i : range(r-1, -1, -1) )
         {
            cycles[i]--;
            if ( cycles[i] == 0 )
            {
               // cycle i -- n-1 --> i+1, ..., n-1, i
               auto tmp = indices[i];
               for ( int j = i; j < n-1; j++ )
               {
                  indices[j] = indices[j+1];
               }
               indices[n-1] = tmp;
               cycles[i] = n - i;
            }
            else
            {
               auto j = cycles[i];
               auto tmp = indices[i];
               indices[i] = indices[n-j];
               indices[n-j] = tmp;
               for ( int k = 0; k < r; k++ ) code[k] = pool[indices[k]];
               codePtrList.push_back(std::make_shared<Code>(Code(code)));
               finish = false;
               break;
            }
         }
      }
   }
};

}; // MasterMind


#endif // __ITERTOOLS_H__
