#ifndef __TEST_ITERTOOLS_H__
#define __TEST_ITERTOOLS_H__

#include <gtest/gtest.h>

#include "itertools.h"


/**
 *
 * ItertoolsTest
 *
 */
/**
 * range
 */
TEST ( ItertoolsTest, rangeTest1 )
{
   Itertools itertools;
   std::vector v{0, 1, 2, 3, 4};
   ASSERT_EQ( itertools.range(0, 5), v );
}
TEST ( ItertoolsTest, rangeTest2 )
{
   Itertools itertools;
   std::vector v{-1, 0, 1, 2, 3, 4};
   ASSERT_EQ( itertools.range(-1, 5), v );
}
TEST ( ItertoolsTest, rangeTest3 )
{
   Itertools itertools;
   std::vector v{5, 4, 3, 2, 1};
   ASSERT_EQ( itertools.range(5, 0, -1), v );
}
TEST ( ItertoolsTest, rangeTest4 )
{
   Itertools itertools;
   std::vector v{2, 1, 0};
   ASSERT_EQ( itertools.range(2, -1, -1), v );
}
/**
 * permutations
 */
TEST ( ItertoolsTest, permutationsTest1 )
{
   Itertools itertools;
   std::vector<ColorType> pool{0,1,2};
   int r = 2;
   CodePtrList codePtrList;
   itertools.permutations(pool, r, codePtrList);

   CodeList ans{
      Code{0,1},
      Code{0,2},
      Code{1,0},
      Code{1,2},
      Code{2,0},
      Code{2,1},
   };

   ASSERT_EQ( codePtrList.size(), ans.size() );
   for ( decltype(ans.size()) i = 0; i < ans.size(); i++ )
   {
      ASSERT_EQ( *codePtrList.at(i), ans.at(i) );
   }
}
TEST ( ItertoolsTest, permutationsTest2 )
{
   Itertools itertools;
   std::vector<ColorType> pool{0,1,2};
   int r = 1;
   CodePtrList codePtrList;
   itertools.permutations(pool, r, codePtrList);

   CodeList ans{
      Code{0},
      Code{1},
      Code{2},
   };

   ASSERT_EQ( codePtrList.size(), ans.size() );
   for ( decltype(ans.size()) i = 0; i < ans.size(); i++ )
   {
      ASSERT_EQ( *codePtrList.at(i), ans.at(i) );
   }
}
TEST ( ItertoolsTest, permutationsTest3 )
{
   Itertools itertools;
   std::vector<ColorType> pool{0,1,2};
   int r = 3;
   CodePtrList codePtrList;
   itertools.permutations(pool, r, codePtrList);

   CodeList ans{
      Code{0,1,2},
      Code{0,2,1},
      Code{1,0,2},
      Code{1,2,0},
      Code{2,0,1},
      Code{2,1,0},
   };

   ASSERT_EQ( codePtrList.size(), ans.size() );
   for ( decltype(ans.size()) i = 0; i < ans.size(); i++ )
   {
      ASSERT_EQ( *codePtrList.at(i), ans.at(i) );
   }
}
/**
 * product
 */
TEST ( ItertoolsTest, product1 )
{
   Itertools itertools;
   std::vector<ColorType> pool{0,1,2};
   int r = 2;
   CodePtrList codePtrList;
   itertools.product(pool, r, codePtrList);

   CodeList ans{
      Code{0,0},
      Code{0,1},
      Code{0,2},
      Code{1,0},
      Code{1,1},
      Code{1,2},
      Code{2,0},
      Code{2,1},
      Code{2,2},
   };

   ASSERT_EQ( codePtrList.size(), ans.size() );
   for ( decltype(ans.size()) i = 0; i < ans.size(); i++ )
   {
      ASSERT_EQ( *codePtrList.at(i), ans.at(i) );
   }
}
TEST ( ItertoolsTest, product2 )
{
   Itertools itertools;
   std::vector<ColorType> pool{0,1,2};
   int r = 1;
   CodePtrList codePtrList;
   itertools.product(pool, r, codePtrList);

   CodeList ans{
      Code{0},
      Code{1},
      Code{2},
   };

   ASSERT_EQ( codePtrList.size(), ans.size() );
   for ( decltype(ans.size()) i = 0; i < ans.size(); i++ )
   {
      ASSERT_EQ( *codePtrList.at(i), ans.at(i) );
   }
}
TEST ( ItertoolsTest, product3 )
{
   Itertools itertools;
   std::vector<ColorType> pool{0,1,2};
   int r = 3;
   CodePtrList codePtrList;
   itertools.product(pool, r, codePtrList);

   CodeList ans{
      Code{0,0,0}, Code{0,0,1}, Code{0,0,2},
      Code{0,1,0}, Code{0,1,1}, Code{0,1,2},
      Code{0,2,0}, Code{0,2,1}, Code{0,2,2},
      Code{1,0,0}, Code{1,0,1}, Code{1,0,2},
      Code{1,1,0}, Code{1,1,1}, Code{1,1,2},
      Code{1,2,0}, Code{1,2,1}, Code{1,2,2},
      Code{2,0,0}, Code{2,0,1}, Code{2,0,2},
      Code{2,1,0}, Code{2,1,1}, Code{2,1,2},
      Code{2,2,0}, Code{2,2,1}, Code{2,2,2},
   };

   ASSERT_EQ( codePtrList.size(), ans.size() );
   for ( decltype(ans.size()) i = 0; i < ans.size(); i++ )
   {
      ASSERT_EQ( *codePtrList.at(i), ans.at(i) );
   }
}


#endif  // __TEST_ITERTOOLS_H__
