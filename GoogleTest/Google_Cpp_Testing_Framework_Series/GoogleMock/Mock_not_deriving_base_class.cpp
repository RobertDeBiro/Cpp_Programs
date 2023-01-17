#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Interface base class
//  - we can also comment this base class when we want to mock it
/*
class DataBaseConnect
{
public:
    virtual bool login(std::string username, std::string password) { return true; }
    virtual bool logout(std::string username) { return true; }
    virtual int fetchRecord() { return -1; }
};
*/

// Mock class
//  - it has the same name as the commented interface base class
//  - the idea in this example is that mock class fully replaces interface base class
//  - this kind of implementation is used if the class that we want to mock contains also some
//    non-virtual functions
//  - in example with inheritance this class was called MockDB
class DataBaseConnect
{
public:
    MOCK_METHOD0(fetchRecord, int());
    MOCK_METHOD1(logout, bool(std::string username));
    MOCK_METHOD2(login, bool(std::string username, std::string pasword));
};

// Component under test class
class MyDatabase
{
    DataBaseConnect& m_dbc;

public:
    MyDatabase(DataBaseConnect& dbc) : m_dbc(dbc) { }

    int InitOnce(std::string username, std::string password) {
        if(m_dbc.login(username, password) != true) {
            std::cout << "\n*****\t DB FAILURE! \t*****\n" << std::endl;
            return -1;
        } else {
            std::cout << "\n*****\t DB SUCCESS! \t*****\n" << std::endl;
            return 1;
        }
    }
};

TEST(MyDBTest, WillOnceTest)
{
    // ***** Arrange *****
    DataBaseConnect mdb;
    MyDatabase db(mdb);

    EXPECT_CALL(mdb, login("Terminator", "I'm Back"))
    .Times(1)
    .WillOnce(testing::Return(true));

    // ***** Act *****
    int retValue = db.InitOnce("Terminator", "I'm Back");

    // ***** Assert *****
    EXPECT_EQ(retValue, 1);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}