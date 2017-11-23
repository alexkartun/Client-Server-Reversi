/*
 * main.cpp
 *	Alex Kartun & Ofir Sharon
 *	324429216   & 204717664
 */
#include "Game.h"
#define SIZE 8
/**
 * Main of the ex3
 * Mecheheuleee
 */
int main() {
	Game reversi;
	reversi.initGame(SIZE); //for this exc we will use define later we will get args from user.
	reversi.startGame();
	while(reversi.getStatus()) {
		reversi.playTurn();
	}
	reversi.endGame();
    return 0;
}
