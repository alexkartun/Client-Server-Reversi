/*
 * main.cpp
 *	Alex Kartun
 *	324429216
 *  Created on: Oct 23, 2017
 *      Author: kartuna
 */
#include "Game.h"
#define SIZE 8
/**
 * Main of the ex2
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
