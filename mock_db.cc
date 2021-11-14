#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "lib/db.hpp"

using namespace std;
using ::testing::Return;
using ::testing::_; // Matcher for parameters

class MockDB : public DataBaseConnect {
public:
    MOCK_METHOD0(fetchRecord, int());
    MOCK_METHOD1(logout, bool(string uname));
    MOCK_METHOD2(login, bool(string uname, string passwd));
    MOCK_METHOD2(login2, bool(string uname, string passwd));
};

TEST(MyDBTest, LoginTest) {
    MockDB mdb;
    MyDatabase db(mdb);
    ON_CALL(mdb, login(_,_)).WillByDefault(Return(true));
    int retValue = 1;
    EXPECT_EQ(retValue, 1);

}
