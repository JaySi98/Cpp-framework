#include <gtest/gtest.h>
#include <tmp/tmp.hpp>

TEST(TmpAddTest, CheckValues)
{
  ASSERT_EQ(tmp::add(1, 2), 3);
  EXPECT_TRUE(true);
}
