/*
 * main.cpp
 *	Alex Kartun & Ofir Sharon
 *	324429216   & 204717664
 */
#include "Game.h"
#define SIZE 8
/**
 * Main of the ex3
 */
int main() {
	Game reversi;
	reversi.initGame(SIZE);
	reversi.startGame();
	//run the loop till end of the game
	while(reversi.getStatus()) {
		reversi.playTurn();
	}
	reversi.endGame();
    return 0;
}
