#include <gtest/gtest.h>

/*
 * TestCaseName:
	- group of related tests
	- International Software Testing Qualifications Board (ISTQB) calls it: Test Suite
 * TestName:
	- Google test
	- ISTQB calls it: Test Case
 * EXPEXT_EQ, EXPECT_TRUE:
	- assertions - statements that check whether condition is true
 */

TEST(TestCaseName, TestName)
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}