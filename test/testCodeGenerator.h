#ifndef __TEST_CODE_GENERATOR_H__
#define __TEST_CODE_GENERATOR_H__

#include <gtest/gtest.h>

#include "codeGenerator.h"

namespace mm = MasterMind;

/**
 *
 * codeGeneratorTest
 *
 */
TEST ( codeGeneratorTest, allCodeGenerator1 )
{
   mm::CodePtrList S;
   int nColors = 2;
   int nPins = 2;
   bool duplicate = false;
   mm::Config config(nColors, nPins, duplicate);
   mm::allCodeGenerator(config, S);
}
TEST ( codeGeneratorTest, allCodeGenerator2 )
{
   mm::CodePtrList S;
   int nColors = 2;
   int nPins = 1;
   bool duplicate = false;
   mm::Config config(nColors, nPins, duplicate);
   mm::allCodeGenerator(config, S);
}
TEST ( codeGeneratorTest, allCodeGenerator3 )
{
   mm::CodePtrList S;
   int nColors = 2;
   int nPins = 2;
   bool duplicate = true;
   mm::Config config(nColors, nPins, duplicate);
   mm::allCodeGenerator(config, S);
}
TEST ( codeGeneratorTest, allCodeGenerator4 )
{
   mm::CodePtrList S;
   int nColors = 1;
   int nPins = 2;
   bool duplicate = true;
   mm::Config config(nColors, nPins, duplicate);
   mm::allCodeGenerator(config, S);
}
TEST ( codeGeneratorTest, allCodeGenerator5 )
{
   mm::CodePtrList S;
   int nColors = 2;
   int nPins = 1;
   bool duplicate = true;
   mm::Config config(nColors, nPins, duplicate);
   mm::allCodeGenerator(config, S);
}

#endif // __TEST_CODE_GENERATOR_H__
