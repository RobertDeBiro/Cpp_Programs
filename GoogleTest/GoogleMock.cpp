#include <iostream>
#include <vector>
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
    virtual bool login(std::string username, std::string password) { return true; }
    virtual bool login2(std::string username, std::string password) { return true; }
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
    MOCK_METHOD2(login, bool(std::string username, std::string pasword));
    MOCK_METHOD2(login2, bool(std::string username, std::string pasword));
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

    int Init(std::string username, std::string password) {
        if(m_dbc.login(username, password) != true) {
            std::cout << "\n*****\t DB FAILURE! \t*****\n" << std::endl;
            return -1;
        } else {
            std::cout << "\n*****\t DB SUCCESS! \t*****\n" << std::endl;
            return 1;
        }
    }

    int Update(std::string username, std::string password) {
        if(m_dbc.login(username, password) != true) {
            if(m_dbc.login(username, password) != true) {
                std::cout << "\n*****\t DB FAILURE! \t*****\n" << std::endl;
                return -1;
            } else {
                std::cout << "\n*****\t DB SUCCESS! \t*****\n" << std::endl;
                return 1;
            }
        } else {
            std::cout << "\n*****\t DB SUCCESS! \t*****\n" << std::endl;
            return 1;
        }
    }

    int Random(std::string username, std::string password) {
        srand(time(0));
        int randomVal = rand() % 2;
        std::cout << "randomVal = " << randomVal << std::endl;
        if (randomVal == 0) {
            m_dbc.login(username, password);
            std::cout << "\n*****\t LOGIN! \t*****\n" << std::endl;
            return 1;
        } else {
            m_dbc.login2(username, password);
            std::cout << "\n*****\t LOGIN2! \t*****\n" << std::endl;
            return 2;
        }
    }

};

TEST(MyDBTest, LoginTest)
{
    // ***** Arrange *****
    MockDB mdb;
    MyDatabase db(mdb); // Originally DataBaseConnect would be passed to db object, but here MockDB is passed

    // Expecting that function login(), with parameters "Terminator" and "I'm Back", will be called
    EXPECT_CALL(mdb, login("Terminator", "I'm Back"))
    .Times(1) // Expect that it will be called once
    .WillOnce(testing::Return(true)); // define that MOCK_METHOD2(login("Terminator", "I'm Back")) will return true

    // ***** Act *****
    int retValue = db.Init("Terminator", "I'm Back"); // db.init ultimately calls MOCK_METHOD2(login...)

    // ***** Assert *****
    EXPECT_EQ(retValue, 1);
}

TEST(MyDBTest, LoginFailure)
{
    // ***** Arrange *****
    MockDB mdb;
    MyDatabase db(mdb);

    EXPECT_CALL(mdb, login(testing::_, testing::_))
    .Times(2)
    .WillRepeatedly(testing::Return(false));

    // ***** Act *****
    int retValue = db.Update("...", "---");

    // ***** Assert *****
    EXPECT_EQ(retValue, -1);
}

TEST(MyDBTest, LoginRandom)
{
    // ***** Arrange *****
    MockDB mdb;
    MyDatabase db(mdb);

    ON_CALL(mdb, login(testing::_, testing::_)).WillByDefault(testing::Return(true));
    ON_CALL(mdb, login2(testing::_, testing::_)).WillByDefault(testing::Return(true));

    // ***** Act *****
    int retValue = db.Random("Random1", "Random2");

    // ***** Assert *****
    EXPECT_EQ(retValue, 2);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}