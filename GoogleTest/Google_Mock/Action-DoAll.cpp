#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Interface base class
class DataBaseConnect
{
public:
    virtual bool login(std::string username, std::string password) { return true; }
    virtual bool logout(std::string username) { return true; }
    virtual int fetchRecord() { return -1; }
};

// Mock class
class MockDB : public DataBaseConnect
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

void DummyFunct() { std::cout << "\n*****\t DUMMY function! \t*****\n"; }

bool DummyFunctRet()
{
    std::cout << "\n*****\t DUMMY function RETURN! \t*****\n";
    return true;
}

TEST(MyDBTest, DoAll)
{
    // ***** Arrange *****
    MockDB mdb;
    MyDatabase db(mdb);

    EXPECT_CALL(mdb, login("Terminator", "I'm Back"))
    .Times(1)
    .WillOnce(testing::DoAll(
                testing::InvokeWithoutArgs(DummyFunct),
                testing::InvokeWithoutArgs(DummyFunct),
                testing::InvokeWithoutArgs(DummyFunctRet)));

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