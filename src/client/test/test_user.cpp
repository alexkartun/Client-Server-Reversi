/*
 * test_user.cpp
 */
#include "gtest/gtest.h"
#include "User.h"
using namespace std;


TEST(UserTest, HandlesInput) {
	User user('x');
	string str = "5 6";
	EXPECT_EQ(user.checkNumericValidation(str), true);
	str = "s 5";
	EXPECT_EQ(user.checkNumericValidation(str), false);
}

TEST(UserTest, HandleCommand) {
	User user('X');
	Logic logic(8);
	logic.possibleMove('X', 'O');
	string input = "3 4";
	EXPECT_EQ(user.checkCommand(input, "Yes", &logic), play);
	input = "3 3";
	EXPECT_EQ(user.checkCommand(input, "Yes", &logic), notvalid);
	input = "close game";
	EXPECT_EQ(user.checkCommand(input, "game", &logic), close_game);
}
