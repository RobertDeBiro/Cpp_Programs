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

// Test placeholder example
TEST(_, _)
{

}

int main(int argc, char** argv)
{
	// Initialize GoogleTest and processes command-line arguments, such as:
	//  - '--gtest_filter'
	//  - '--gtest_output'
	testing::InitGoogleTest(&argc, argv);

	// Run all test cases and returns an exit code based on the test results
	//  - it is required to execute the registered tests - without it, no tests will run
	return RUN_ALL_TESTS();
}
