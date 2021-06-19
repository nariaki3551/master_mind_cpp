#ifndef __TEST_UTILS_H__
#define __TEST_UTILS_H__

#include <gtest/gtest.h>

#include "utils.h"

namespace mm = MasterMind;


/**
 *
 * utilsTest
 *
 */
TEST ( countHitBlowTest, countHitBlowTest1 )
{
   mm::Code codeA{ 0, 0 };
   mm::Code codeB{ 0, 0 };
   mm::Config config{2, 2, true};
   ASSERT_EQ( countHitBlow(codeA, codeB, config), mm::HitBlow(2, 0) );
}

TEST ( countHitBlowTest, countHitBlowTest2 )
{
   mm::Code codeA{ 0, 0 };
   mm::Code codeB{ 0, 1 };
   mm::Config config{2, 2, true};
   ASSERT_EQ( countHitBlow(codeA, codeB, config), mm::HitBlow(1, 0) );
}

TEST ( countHitBlowTest, countHitBlowTest3 )
{
   mm::Code codeA{ 0, 0 };
   mm::Code codeB{ 1, 1 };
   mm::Config config{2, 2, true};
   ASSERT_EQ( countHitBlow(codeA, codeB, config), mm::HitBlow(0, 0) );
}


#endif  // __TEST_UTILS_H__
