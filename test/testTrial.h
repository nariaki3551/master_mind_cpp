#ifndef __TEST_TRIAL_H__
#define __TEST_TRIAL_H__

#include <gtest/gtest.h>

#include "trial.h"

namespace mm = MasterMind;

/**
 *
 * trialTest
 *
 */
TEST ( trialTest, test )
{
   mm::CodePtr codeA(new mm::Code{ 0, 0 });
   mm::CodePtr codeB(new mm::Code{ 1, 0 });
   mm::CodePtr codeC(new mm::Code{ 0, 1 });
   mm::CodePtr codeD(new mm::Code{ 1, 1 });
   mm::CodePtrList S{ codeA, codeB, codeC, codeD };

   int nColors = 2, nPins = 2;
   bool duplicate = true, interactive = false;
   mm::Config config(nColors, nPins, duplicate, interactive);
   config.setSecret(mm::Code{0, 1});

   mm::Code guess = mm::Code{1, 1};
   mm::trial(S, guess, config);  // (hit, blow) = (1, 0)
   mm::CodePtrList reduceS{ codeB, codeC };
   ASSERT_EQ( S, reduceS );
}


#endif // __TEST_TRIAL_H__
