/*
 * test_logic.cpp
 */
#include "gtest/gtest.h"
#include "Logic.h"
using namespace std;

TEST(LogicTest, HandlesMinMaxValue) {
	Logic logic(8);
	logic.possibleMove('X', 'O');
	int sold = 2;
	logic.finishMove(4, 3, 'X', &sold, &sold);
	logic.possibleMove('O', 'X');
	EXPECT_EQ(logic.minMaxAlgorithm('X', 4, 'O', 1), Move(2, 2));
}

TEST(LogicTest, HandlesBestOponentMove) {
	Logic logic(8);
	logic.possibleMove('X', 'O');
	int sold = 2;
	logic.finishMove(3, 4, 'X', &sold, &sold);
	logic.possibleMove('O', 'X');
	logic.finishMove(3, 5, 'O', &sold, &sold);
	logic.possibleMove('X', 'O');
	EXPECT_EQ(logic.bestOpponentMove(3, 3) , 5);
}
