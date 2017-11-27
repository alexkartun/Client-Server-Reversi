/*
 * test_board.cpp
 *	Alex Kartun & Ofir Sharon
 *	324429216   & 204717664
 */
#include "gtest/gtest.h"
#include "Console.h"
using namespace std;

TEST(BoardTest, HandlesIvalidArgument) {
	Console c(8);
	EXPECT_THROW(c.setValue(-3, 2, 'X'), invalid_argument);
	EXPECT_THROW(c.getValue(-3, 2), invalid_argument);
	EXPECT_THROW(c.getValue(-9, 2), invalid_argument);
	EXPECT_THROW(c.setValue(9, 2, 'X'), invalid_argument);
	EXPECT_EQ(c.getValue(3, 3), 'O');
}
