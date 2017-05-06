#include <iostream>
#include <gtest/gtest.h>

#include <Odbcslap.hpp>

// The fixture for testing class OdbcslapTest1. From google test primer.
class OdbcslapTest1 : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    OdbcslapTest1() {
      // You can do set-up work for each test here.
    }

    virtual ~OdbcslapTest1() {
      // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp() {
      // Code here will be called immediately after the constructor (right
      // before each test).
      o = Odbcslap(getenv("TEST_DSN"), {"Select 'hello world'"});
    }

    virtual void TearDown() {
      // Code here will be called immediately after each test (right
      // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Project1.
    Odbcslap o;
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(OdbcslapTest1, CanConnectToMysql) {
bool status = o.connect();
EXPECT_EQ(true, status);
}