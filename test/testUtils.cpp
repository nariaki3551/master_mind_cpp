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
/**
 * countHitBlow
 */
TEST ( countHitBlowTest, countHitBlowTest1 )
{
   auto codeA = mm::createPtr(mm::Code{ 0, 0 });
   auto codeB = mm::createPtr(mm::Code{ 0, 0 });
   mm::Config config{2, 2, true};
   ASSERT_EQ( countHitBlow(codeA, codeB, config), mm::Hint(2, 0) );

   for ( auto &item : mm::lruCacheOfCountHitBlow )
   {
      std::cout << "CodePtrPair " << mm::strCode(item.first.first) << ", " << mm::strCode(item.first.second) << std::endl;
      std::cout << "  Hint" << item.second.first << ", " << item.second.second << std::endl;
   }
}

TEST ( countHitBlowTest, countHitBlowTest2 )
{
   auto codeA = mm::createPtr(mm::Code{ 0, 0 });
   auto codeB = mm::createPtr(mm::Code{ 0, 1 });
   mm::Config config{2, 2, true};
   ASSERT_EQ( countHitBlow(codeA, codeB, config), mm::Hint(1, 0) );
}

TEST ( countHitBlowTest, countHitBlowTest3 )
{
   auto codeA = mm::createPtr(mm::Code{ 0, 0 });
   auto codeB = mm::createPtr(mm::Code{ 1, 1 });
   mm::Config config{2, 2, true};
   ASSERT_EQ( countHitBlow(codeA, codeB, config), mm::Hint(0, 0) );
}

/**
 * strCode
 */
TEST ( strCodeTest, strCodeTest1 )
{
   mm::Code codeA{0, 0};
   mm::strCode(codeA);
}
TEST ( strCodeTest, strCodeTest2 )
{
   auto codeA = mm::createPtr(mm::Code{0, 0});
   mm::strCode(codeA);
}

/**
 * copy
 */
TEST ( copyTest, copyTest1 )
{
   auto codeA = mm::createPtr(mm::Code{0});
   auto codeB = mm::createPtr(mm::Code{1});
   auto codeC = mm::createPtr(mm::Code{2});
   mm::CodePtrList codePtrList{
      codeA, codeB, codeC
   };
   mm::CodePtrList copied = mm::copy(codePtrList);
   ASSERT_EQ( codePtrList.size(), copied.size() );
   for ( decltype(copied.size()) i = 0; i < copied.size(); i++ )
   {
      ASSERT_EQ( *copied[i], *codePtrList[i] );
   }
}

#endif  // __TEST_UTILS_H__
