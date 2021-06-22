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
         ) noexcept;


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
         ) noexcept;


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
         ) noexcept;

};

}; // MasterMind


#endif // __ITERTOOLS_H__
