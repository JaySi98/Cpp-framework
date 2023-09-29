#include <gtest/gtest.h>
#include <tmp/tmp.hpp>

TEST(Placeholder, AlwaysPass)
{
  ASSERT_EQ(2,2);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
