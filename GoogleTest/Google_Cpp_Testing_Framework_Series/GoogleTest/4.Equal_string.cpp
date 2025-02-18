#include <gtest/gtest.h>

class MyClass
{
    std::string m_id;

public:
    MyClass(std::string id) : m_id{ id } {}
    std::string getId() { return m_id; }
};

// Test case behaves like a normal C++ function, hence I can use custom  made classes
//  - but, as with other funcitons, in order to use class, class definition must be visible
TEST(StringEqual, root)
{
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
