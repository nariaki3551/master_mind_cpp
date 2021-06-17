#ifndef __TEST_UTILS_H__
#define __TEST_UTILS_H__

#include <gtest/gtest.h>

#include "utils.h"


/**
 *
 * utilsTest
 *
 */
TEST ( countHitBlowTest, countHitBlowTest1 )
{
   Code codeA{ 0, 0 };
   Code codeB{ 0, 0 };
   Config config{2, 2, true};
   ASSERT_EQ( countHitBlow(codeA, codeB, config), HitBlow(2, 0) );
}

TEST ( countHitBlowTest, countHitBlowTest2 )
{
   Code codeA{ 0, 0 };
   Code codeB{ 0, 1 };
   Config config{2, 2, true};
   ASSERT_EQ( countHitBlow(codeA, codeB, config), HitBlow(1, 0) );
}

TEST ( countHitBlowTest, countHitBlowTest3 )
{
   Code codeA{ 0, 0 };
   Code codeB{ 1, 1 };
   Config config{2, 2, true};
   ASSERT_EQ( countHitBlow(codeA, codeB, config), HitBlow(0, 0) );
}


#endif  // __TEST_UTILS_H__
