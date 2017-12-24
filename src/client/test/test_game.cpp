/*
 * test_game.cpp
 */
#include "gtest/gtest.h"
#include "Game.h"
using namespace std;

TEST(GameTest, HandlesInvalidArgument) {
	Game reversi(2, 8);
	EXPECT_THROW(reversi.initGame(0), invalid_argument);
	EXPECT_THROW(reversi.initGame(-5), invalid_argument);
}

TEST(GameTest, HandlesStopGame) {
	Game reversi(2, 8);
	reversi.initGame(2);
	reversi.startGame();
	reversi.makeTurn();
	reversi.makeTurn();
	EXPECT_EQ(reversi.getStatus(), false);
}
