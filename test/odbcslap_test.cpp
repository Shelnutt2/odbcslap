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
      oDsnOnly = std::unique_ptr<Odbcslap>(new Odbcslap(getenv("ODBCSLAP_TEST_DSN"), {"Select 'hello world'"},
                                                        100, 1, false));
      oUsernamePassword = std::unique_ptr<Odbcslap>(new Odbcslap(getenv("ODBCSLAP_TEST_DSN_NO_PW"),
                                                                 getenv("ODBCSLAP_TEST_USERNAME"),
                                                                 getenv("ODBCSLAP_TEST_PASSWORD"),
                                                                 {"Select 'hello world'"}, 100, 1, false));
    }

    virtual void TearDown() {
      // Code here will be called immediately after each test (right
      // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Project1.
    std::unique_ptr<Odbcslap> oDsnOnly;
    std::unique_ptr<Odbcslap> oUsernamePassword;
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(OdbcslapTest1, CanConnectWithDNSOnly) {
  oDsnOnly->benchmark();

  EXPECT_LE(0, oDsnOnly->getQueries()[0]->getAverage_query_times());
}

TEST_F(OdbcslapTest1, ThreadedBenchmark) {
  oDsnOnly->setThreads(10);
  oDsnOnly->benchmark();

  EXPECT_LE(0, oDsnOnly->getQueries()[0]->getAverage_query_times());
}

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
/*
TEST_F(OdbcslapTest1, CanConnectWithDNSUsernameAndPassword) {
  bool status = oUsernamePassword.connect();
  EXPECT_EQ(true, status);
}*/
