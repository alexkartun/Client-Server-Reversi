/*
 * test_logic.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: ofir
 */
#include "gtest/gtest.h"
#include "Logic.h"

using namespace std;

TEST(LogicTest, HandlesDestroyesEnemies) {
	Logic logic(8);
	logic.possibleMove('X', 'O');
	logic.finishMove(4, 3, 'X');
	EXPECT_EQ(logic.getDestroyed(), 1);
}


