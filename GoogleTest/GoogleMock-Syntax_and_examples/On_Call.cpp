/*
Every time ON_CALL is called we get GMOCK WARNING saying:
"Uninteresting mock function call - taking default action specified at ..."
*/

#include <iostream>
#include <ctime>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

/*
 * Interface class
   - interface class doesn't have to be Abstract (Interface in OOP sense), bur rather class that is used
     as an interface towards some external resource, such as database
*/
class DataBaseConnect
{
public:
    virtual bool login0(std::string username, std::string password) { return true; }
    virtual bool login1(std::string username, std::string password) { return true; }
    virtual bool logout(std::string username) { return true; }
    virtual int fetchRecord() { return -1; }
};

/*
 * Mock class
   - mock class usually derives from interface class
   - needs to implement interface class methods
*/
class MockDB : public DataBaseConnect
{
public:
    MOCK_METHOD0(fetchRecord, int());
    MOCK_METHOD1(logout, bool(std::string username));
    MOCK_METHOD2(login0, bool(std::string username, std::string pasword));
    MOCK_METHOD2(login1, bool(std::string username, std::string pasword));
};

/*
 * Component under test i.e. tested class
   - this class interacts with interface class
   - in order to test it, it is needed to construct this class with mock class
     rather then with interface class
*/
class MyDatabase
{
    DataBaseConnect& m_dbc;

public:
    MyDatabase(DataBaseConnect& dbc) : m_dbc(dbc) { }

    int Random(std::string username, std::string password) {
        // Generate random number
        srand(static_cast<unsigned int>(std::time(nullptr)));
        int randomVal = rand() % 2;
        std::cout << "Generating random number:\n";
        std::cout << "randomVal = " << randomVal << std::endl;

        if (randomVal == 0) {
            m_dbc.login0(username, password);
            std::cout << "\n*****\t LOGIN 0! \t*****\n" << std::endl;
        } else {
            m_dbc.login1(username, password);
            std::cout << "\n*****\t LOGIN 1! \t*****\n" << std::endl;
        }
        return 1;
    }
};

TEST(MyDBTest, On_Call_Once)
{
    // ***** Arrange *****
    MockDB mdb;
    MyDatabase db(mdb);

    /*
    When login0 is called it is printed:
        GMOCK WARNING:
        Uninteresting mock function call - taking default action specified at:
        C:\Users\rar\Desktop\Posao\Programs\VSCode\Cpp\GoogleTest\GMock-On_Call.cpp:86:
            Function call: login0("Random1", "Random2")
                Returns: true

    When login0 is not called it is printed:
        GMOCK WARNING:
        Uninteresting mock function call - returning default value.
            Function call: login1("Random1", "Random2")
                Returns: false
    */
    ON_CALL(mdb, login0(testing::_, testing::_))
    .WillByDefault(testing::Return(true));

    // ***** Act *****
    int retValue = db.Random("Random1", "Random2");

    // ***** Assert *****
    //  - this is actually not needed since we will always have value 1
    EXPECT_EQ(retValue, 1);
}

TEST(MyDBTest, On_Call_Twice)
{
    // ***** Arrange *****
    MockDB mdb;
    MyDatabase db(mdb);

    /*
    When login0 is called it is printed:
        GMOCK WARNING:
        Uninteresting mock function call - taking default action specified at:
        C:\Users\rar\Desktop\Posao\Programs\VSCode\Cpp\GoogleTest\GMock-On_Call.cpp:118:
            Function call: login1("Random1", "Random2")
                Returns: true

    When login1 is called it is printed:
        GMOCK WARNING:
        Uninteresting mock function call - taking default action specified at:
        C:\Users\rar\Desktop\Posao\Programs\VSCode\Cpp\GoogleTest\GMock-On_Call.cpp:121:
            Function call: login1("Random1", "Random2")
                Returns: true
    */
    ON_CALL(mdb, login0(testing::_, testing::_))
    .WillByDefault(testing::Return(true));

    ON_CALL(mdb, login1(testing::_, testing::_))
    .WillByDefault(testing::Return(true));

    // ***** Act *****
    int retValue = db.Random("Random1", "Random2");
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}