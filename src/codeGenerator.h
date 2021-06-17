#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__

#include <cassert>

#include "def.h"
#include "utils.h"
#include "itertools.h"


/**
* @fn CodeList allCodeGenerator(Config &config, CodeList &codeList)
* @brief 全てのコード配列を列挙する.
* @param[in] config パラメタ
* @param[out] codeList コード配列
* @return CodeList
*/
void allCodeGenerator(
      Config &config,
      CodeList &codeList
      )
{
   assert( codeList.size() == 0 );
   Itertools itertools;
   auto colors = itertools.range(0, config.nColors);
   if( config.duplicate )
   {
      itertools.product(colors, config.nPins, codeList);
   }
   else
   {
      itertools.permutations(colors, config.nPins, codeList);
   }
}


#endif // __CODE_GENERATOR_H__
