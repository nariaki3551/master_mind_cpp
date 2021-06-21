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
/**
 * codeGeneratorTest
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

/**
 * getGuessCandidatesTest
 */
TEST ( codeGeneratorTest, getGuessCandidatesTest1 )
{
   int nColors = 2;
   int nPins = 2;
   bool duplicate = true;
   mm::Config config(nColors, nPins, duplicate);

   mm::CodePtrList S;
   mm::allCodeGenerator(config, S);

   mm::CodeList guessHist;
   mm::CodePtrList G;
   setGuessCandidates(S, guessHist, config, G);
   // [0, 0], [0, 1]
   ASSERT_EQ( G.size(), 2 );
   ASSERT_EQ( *G[0], (mm::Code{0, 0}) );
   ASSERT_EQ( *G[1], (mm::Code{0, 1}) );
}
TEST ( codeGeneratorTest, getGuessCandidatesTest2 )
{
   int nColors = 2;
   int nPins = 2;
   bool duplicate = true;
   mm::Config config(nColors, nPins, duplicate);

   mm::CodePtrList S;
   mm::allCodeGenerator(config, S);

   mm::CodeList guessHist{ mm::Code{0, 0} };
   mm::CodePtrList G;
   setGuessCandidates(S, guessHist, config, G);
   // [0, 0], [0, 1], [1, 0], [1, 1]
   ASSERT_EQ( G.size(), 4 );
   ASSERT_EQ( *G[0], (mm::Code{0, 0}) );
   ASSERT_EQ( *G[1], (mm::Code{0, 1}) );
   ASSERT_EQ( *G[2], (mm::Code{1, 0}) );
   ASSERT_EQ( *G[3], (mm::Code{1, 1}) );
}
TEST ( codeGeneratorTest, getGuessCandidatesTest3 )
{
   int nColors = 3;
   int nPins = 2;
   bool duplicate = true;
   mm::Config config(nColors, nPins, duplicate);

   mm::CodePtrList S;
   mm::allCodeGenerator(config, S);

   mm::CodeList guessHist{ mm::Code{0, 0} };
   mm::CodePtrList G;
   setGuessCandidates(S, guessHist, config, G);
   // [0, 0], [0, 1], [1, 0], [1, 1], [1, 2]
   ASSERT_EQ( G.size(), 5 );
   ASSERT_EQ( *G[0], (mm::Code{0, 0}) );
   ASSERT_EQ( *G[1], (mm::Code{0, 1}) );
   ASSERT_EQ( *G[2], (mm::Code{1, 0}) );
   ASSERT_EQ( *G[3], (mm::Code{1, 1}) );
   ASSERT_EQ( *G[4], (mm::Code{1, 2}) );
}


#endif // __TEST_CODE_GENERATOR_H__
