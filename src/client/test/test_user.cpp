/*
 * test_user.cpp
 */
#include "gtest/gtest.h"
#include "User.h"
using namespace std;


TEST(UserTest, HandlesInput) {
	User user('x');
	string str = "5 6";
	EXPECT_EQ(user.checkValidation(str), true);
	str = "s 5";
	EXPECT_EQ(user.checkValidation(str), false);
}

