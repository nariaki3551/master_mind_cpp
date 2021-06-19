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
TEST ( policyTest, policy )
{
   mm::CodePtr codeA(new mm::Code{ 0, 0 });
   mm::CodePtr codeB(new mm::Code{ 1, 0 });
   mm::CodePtr codeC(new mm::Code{ 0, 1 });
   mm::CodePtr codeD(new mm::Code{ 1, 1 });
   mm::CodePtrList S{ codeA, codeB, codeC, codeD };
   mm::policy(S, S);
}


#endif // __TEST_POLICY_H__
