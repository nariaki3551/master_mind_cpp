#ifndef __TEST_POLICY_H__
#define __TEST_POLICY_H__

#include <gtest/gtest.h>

#include "policy.h"

namespace mm = MasterMind;

/**
 *
 * policyTest
 *
 */
TEST ( policyTest, randomPolicy1 )
{
   mm::CodePtr codeA(new mm::Code{ 0, 0 });
   mm::CodePtr codeB(new mm::Code{ 1, 0 });
   mm::CodePtr codeC(new mm::Code{ 0, 1 });
   mm::CodePtr codeD(new mm::Code{ 1, 1 });
   mm::CodePtrList S{ codeA, codeB, codeC, codeD };
   mm::Config config{2, 2, true, false, "random"};
   mm::policy(S, S, config);
}

TEST ( policyTest, minmaxPolicy1 )
{
   mm::CodePtr codeA(new mm::Code{ 0, 0 });
   mm::CodePtr codeB(new mm::Code{ 1, 0 });
   mm::CodePtr codeC(new mm::Code{ 0, 1 });
   mm::CodePtr codeD(new mm::Code{ 1, 1 });
   mm::CodePtrList S{ codeA, codeB, codeC, codeD };
   mm::Config config{2, 2, true, false, "minmax"};
   mm::policy(S, S, config);
}

TEST ( policyTest, expMinmaxPolicy1 )
{
   mm::CodePtr codeA(new mm::Code{ 0, 0 });
   mm::CodePtr codeB(new mm::Code{ 1, 0 });
   mm::CodePtr codeC(new mm::Code{ 0, 1 });
   mm::CodePtr codeD(new mm::Code{ 1, 1 });
   mm::CodePtrList S{ codeA, codeB, codeC, codeD };
   mm::Config config{2, 2, true, false, "exp_minmax"};
   mm::policy(S, S, config);
}

TEST ( policyTest, entropyPolicy1 )
{
   mm::CodePtr codeA(new mm::Code{ 0, 0 });
   mm::CodePtr codeB(new mm::Code{ 1, 0 });
   mm::CodePtr codeC(new mm::Code{ 0, 1 });
   mm::CodePtr codeD(new mm::Code{ 1, 1 });
   mm::CodePtrList S{ codeA, codeB, codeC, codeD };
   mm::Config config{2, 2, true, false, "entropy"};
   mm::policy(S, S, config);
}
#endif // __TEST_POLICY_H__
