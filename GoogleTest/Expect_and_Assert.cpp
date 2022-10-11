#include <iostream>
#include <gtest/gtest.h>

TEST(Assertions, CheckAssert)
{
	// Success scenario
	ASSERT_TRUE(1 == 1);
	ASSERT_FALSE(1 == 2);

	// Failure scenario
	ASSERT_TRUE(1 == 2);

	// When one of previous ASSERTs fails, following text won't be printed
	std::cout << "Assert finished!\n";
}

TEST(Assertions, CheckExcept)
{
	// Success scenarios
	EXPECT_TRUE(1 == 1);
	EXPECT_FALSE(1 == 2);

	// Failure scenario
	EXPECT_FALSE(1 == 1);

	std::cout << "Expect finished!\n";
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}