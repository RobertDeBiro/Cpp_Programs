#include <iostream>
#include <gtest/gtest.h>

TEST(Assertions, CheckAssert)
{
	// Success scenario
	ASSERT_TRUE(1 == 1);
	ASSERT_FALSE(1 == 2);

	// Failure scenario
	//  - when ASSERT fails, test will fail and stop executing
	//  - "Assert finished!" won't be printed
	ASSERT_TRUE(1 == 2);

	std::cout << "Assert finished!\n";
}

TEST(Assertions, CheckExcept)
{
	// Success scenarios
	EXPECT_TRUE(1 == 1);
	EXPECT_FALSE(1 == 2);

	// Failure scenario
	//  - when EXPECT fails, test will fail, but it will continue with execution
	//  - "Expect finished!" will be printed
	EXPECT_FALSE(1 == 1);

	std::cout << "Expect finished!\n";
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
