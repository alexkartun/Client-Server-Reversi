/*
 * test_logic.cpp
 *	Alex Kartun & Ofir Sharon
 *	324429216   & 204717664
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

TEST(LogicTest, HandlesInput) {
	Logic logic(8);
	int num;
	EXPECT_EQ(logic.inputNumericValidation("10", &num), true);
	EXPECT_EQ(logic.inputNumericValidation("hh", &num), false);
}

TEST(LogicTest, HandlesMinMaxValue) {
	Logic logic(8);
	logic.possibleMove('X', 'O');
	logic.finishMove(4, 3, 'X');
	logic.possibleMove('O', 'X');
	EXPECT_EQ(logic.minMaxAlgorithm('X', 4, 'O', 1), Logic::Move(2, 2));
}

TEST(LogicTest, HandlesBestOponentMove) {
	Logic logic(8);
	logic.possibleMove('X', 'O');
	logic.finishMove(3, 4, 'X');
	logic.possibleMove('O', 'X');
	logic.finishMove(3, 5, 'O');
	logic.possibleMove('X', 'O');
	EXPECT_EQ(logic.bestOpponentMove(3, 3) , 5);
}
