#include "factorial.h"

#include "gtest/gtest.h"

#include <stdexcept>


TEST(FactorialTest, BaseTest) {
    ASSERT_EQ(factorial(0), 1);
    ASSERT_EQ(factorial(1), 1);
    ASSERT_EQ(factorial(2), 2);
    ASSERT_EQ(factorial(3), 6);
    ASSERT_EQ(factorial(4), 24);
    ASSERT_EQ(factorial(5), 120);
    ASSERT_EQ(factorial(6), 720);
    ASSERT_EQ(factorial(7), 5'040);
    ASSERT_EQ(factorial(8), 40'320);
    ASSERT_EQ(factorial(9), 362'880);
}


TEST(FactorialTest, Exceptions) {
    ASSERT_THROW(factorial(-10), std::runtime_error);
    ASSERT_THROW(factorial(1.4), std::runtime_error);
}
