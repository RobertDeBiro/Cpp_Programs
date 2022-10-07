#include <iostream>
#include <gtest/gtest.h>

class MyClass
{
    std::string m_id;

public:
    MyClass(std::string id) : m_id{ id } {}
    std::string getId() { return m_id; }
};

TEST(AAA, Increment_by_5) {
	// Arrange
    int value = 100;
    int increment = 5;

    // Act
    value += increment;

    // Assert
    ASSERT_EQ(value, 105);
}

TEST(AAA, Increment_by_10) {
	// Arrange
    int value = 100;
    int increment = 10;

    // Act
    value += increment;

    // Assert
    ASSERT_EQ(value, 110);
}

TEST(AAA_Class, String) {
    // Arrange
    MyClass mc("root");

    // Act
    std::string value = mc.getId();

    // Assert
    ASSERT_STREQ(value.c_str(), "root");
    // ASSERT_EQ(value.c_str(), "root"); // -> This fails!
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}