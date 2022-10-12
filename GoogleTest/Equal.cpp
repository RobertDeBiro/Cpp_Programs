#include <gtest/gtest.h>

TEST(Equal, Increment_by_5)
{
	// Arrange
    int value = 100;
    int increment = 5;

    // Act
    value += increment;

    // Assert
    ASSERT_EQ(value, 105);
}

TEST(Equal, Increment_by_10)
{
	// Arrange
    int value = 100;
    int increment = 10;

    // Act
    value += increment;

    // Assert
    EXPECT_EQ(value, 110);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}