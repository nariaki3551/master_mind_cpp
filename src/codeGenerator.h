#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__

#include <cassert>

#include "def.h"
#include "utils.h"
#include "itertools.h"


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


#endif // __CODE_GENERATOR_H__
