#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "lib/db.hpp"

using namespace std;
using ::testing::Return;
using ::testing::_; // Matcher for parameters

class MockDB : public DataBaseConnect {
public:
    MOCK_METHOD0(fetchRecord, int());
    MOCK_METHOD1(redis, bool(string uname));
    MOCK_METHOD2(aeroSpike, bool(string uname, string passwd));
    MOCK_METHOD2(mysql, bool(string uname, string passwd));
};

TEST(MyDBTest0, LoginTest) {
    //case 1
    MockDB mdb;
    MyDatabase* x = new MyDatabase (mdb);
    EXPECT_CALL(mdb,redis("x")).WillOnce(Return(true));
    EXPECT_EQ(x->loginWrapper(), true);

}


TEST(MyDBTest1, LoginTest) {
    //case 2
    MockDB mdb;
    MyDatabase* x = new MyDatabase (mdb);
    EXPECT_CALL(mdb,redis("x")).WillOnce(Return(false));
    EXPECT_CALL(mdb,aeroSpike("x","y")).WillOnce(Return(true));
    EXPECT_EQ(x->loginWrapper(), false);

}


TEST(MyDBTest2, LoginTest) {
    //case 3
    MockDB mdb;
    MyDatabase* x = new MyDatabase (mdb);
    EXPECT_CALL(mdb,redis("x")).WillOnce(Return(false));
    EXPECT_CALL(mdb,aeroSpike("x","y")).WillOnce(Return(false));
    EXPECT_CALL(mdb,mysql("x","y")).WillOnce(Return(true));
    EXPECT_EQ(x->loginWrapper(), true);
}


TEST(MyDBTest3, LoginTest) {
    //case 4
    MockDB mdb;
    MyDatabase* x = new MyDatabase (mdb);
    EXPECT_CALL(mdb,redis("x")).WillOnce(Return(false));
    EXPECT_CALL(mdb,aeroSpike("x","y")).WillOnce(Return(false));
    EXPECT_CALL(mdb,mysql("x","y")).WillOnce(Return(false));
    EXPECT_EQ(x->loginWrapper(), false);

}