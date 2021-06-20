#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__

#include <cassert>
#include <set>

#include "def.h"
#include "utils.h"
#include "itertools.h"

namespace MasterMind
{

/**
* @fn CodePtrList allCodeGenerator(Config &config, CodePtrList &codePtrList)
* @brief 全てのコード配列を列挙する.
* @param[in] config パラメタ
* @param[out] codePtrList コード配列
*/
void allCodeGenerator(
      Config &config,
      CodePtrList &codePtrList
      )
{
   assert( codePtrList.size() == 0 );
   Itertools itertools;
   auto colors = itertools.range<ColorType>(0, config.nColors);
   if( config.duplicate )
   {
      itertools.product(colors, config.nPins, codePtrList);
   }
   else
   {
      itertools.permutations(colors, config.nPins, codePtrList);
   }
}


/**
 * @fn void setGuessCandidates(CodePtrList &codePtrList, CodeList &guessHist,
 *             Config &config,CodePtrList &guessCandidates)
 * @brief 推測コード集合を計算する
 * @param[in] codePtrList コード集合
 * @param[in] guessHist 推測履歴
 * @param[in] config パラメタ
 * @param[out] guessCandidates 推測コード集合
 * @details まだ推測に使用されていない色についての区別は行わない
 */
void setGuessCandidates(
      CodePtrList &codePtrList,
      CodeList &guessHist,
      Config &config,
      CodePtrList &guessCandidates
      )
{
   assert ( guessCandidates.size() == 0 );

   // get colors used in guesses
   std::set<ColorType> histColors;
   for ( auto guess : guessHist )
   {
      for ( auto color : guess )
      {
         histColors.insert(color);
      }
   }

   if ( static_cast<int>(histColors.size()) >= config.nColors - 1 )
   {
      guessCandidates = codePtrList;
      return;
   }

   Itertools itertools;
   auto colors = itertools.range<ColorType>(0, config.nColors);
   ColorType minColorNotInHist = -1;
   for ( auto color : colors )
   {
      if ( histColors.find(color) == histColors.end() )
      {
         minColorNotInHist = color;
         break;
      }
   }
   assert( minColorNotInHist != -1 );

   // extract guess code
   for ( auto code : codePtrList )
   {
      int tmp = -1;
      bool insert = true;
      for ( auto color : *code )
      {
         if ( histColors.find(color) == histColors.end() )
         {
            if ( tmp == -1 && color != minColorNotInHist )
            {
               insert = false;
               break;
            }
            else if ( color < tmp )
            {
               insert = false;
               break;
            }
            tmp = color;
         }
      }
      if ( insert )
      {
         guessCandidates.push_back(code);
      }
   }
}

}; // MasterMind


#endif // __CODE_GENERATOR_H__
