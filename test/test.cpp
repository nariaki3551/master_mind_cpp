#include <gtest/gtest.h>
#include "utils.h"

TEST ( countHitBlowTest, countHitBlowTest1 )
{
   Code codeA{ 0, 0 };
   Code codeB{ 0, 0 };
   ASSERT_EQ( countHitBlow(codeA, codeB), HitBlow(2, 0) );
}

TEST ( countHitBlowTest, countHitBlowTest2 )
{
   Code codeA{ 0, 0 };
   Code codeB{ 0, 1 };
   ASSERT_EQ( countHitBlow(codeA, codeB), HitBlow(1, 0) );
}

TEST ( countHitBlowTest, countHitBlowTest3 )
{
   Code codeA{ 0, 0 };
   Code codeB{ 1, 1 };
   ASSERT_EQ( countHitBlow(codeA, codeB), HitBlow(0, 0) );
}
