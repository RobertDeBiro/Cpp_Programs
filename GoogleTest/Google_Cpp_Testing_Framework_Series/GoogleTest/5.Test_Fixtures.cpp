/*
- if we initialize some class or structure into several test cases, we will have a lot of duplicated code
- in order to reduce lines of code we can use TestFixtures which calls the 'testing::Test' class
  that initialize our class by using SetUp() and TearDown()
    - when 'TEST_F' is called, 'SetUp()' function is executed
    - when 'TEST_F' is finished, 'TearDown()' is executed
*/

#include <gtest/gtest.h>

// Normal class and tests
class MyClass
{
    int m_baseValue;

public:
    MyClass(int baseValue) : m_baseValue{ baseValue } {}
    
    void increment(int byValue) { m_baseValue += byValue; }
    int getValue() { return m_baseValue; }
};

TEST(MyClass_TestCase, Increment_by_5)
{
    // Arrange
    //  - initialize MyClass object
    MyClass mc(100);
    // Act
    mc.increment(5);
    // Assert
    ASSERT_EQ(mc.getValue(), 105);
}

TEST(MyClass_TestCase, Increment_by_10)
{
    // Arrange
    //  - initialize MyClass object
    MyClass mc(100);
    // Act
    mc.increment(10);
    // Assert
    ASSERT_EQ(mc.getValue(), 110);
}


// TestFixture class and test
//  - this class is used for setting up "Arrange" part from other tests
struct MyClassTest : public testing::Test
{
    MyClass *mc;

    // 'SetUp()' and 'TearDown()' are overridding 'testing::Test' class functions
    void SetUp()
    {
        std::cout << "\n*****\t Calling setUp()! \t*****\n";
        mc = new MyClass(100);
    }
    void TearDown()
    {
        std::cout << "\n*****\t Calling tearDown()! \t*****\n";
        delete mc;
    }
};

/*
 * TEST_F(ClassName, TestName)
 *  - ClassName (or StructName) is the name of class that inherits testing::Test
 */
TEST_F(MyClassTest, Increment_by_5)
{
    // Act
    mc->increment(5);
    // Assert
    ASSERT_EQ(mc->getValue(), 105);
}

TEST_F(MyClassTest, Increment_by_10)
{
    // Act
    mc->increment(10);
    // Assert
    ASSERT_EQ(mc->getValue(), 110);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
