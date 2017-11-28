/*
 * main.cpp
 */
#include "Game.h"
#define SIZE 8
#include <iostream>
using namespace std;

/**
 * Main of the ex3
 */
int main() {
	cout << "Please input 'user' if you want to play vs other player or 'cpu' to play vs computer: ";
	string input;
	//this loop will run till you input cpu or user as your choose
	do {
		getline(cin, input);
		if (input.compare("user") == 0 || input.compare("cpu") == 0) {
			break;
		} else {
				cout << "Please enter your choose again correctly: ";
		}
	} while(true);
	Game reversi(input);
	reversi.initGame(SIZE);
	reversi.startGame();
	//run the loop till end of the game
	while(reversi.getStatus()) {
		reversi.playTurn();
	}
	reversi.endGame();
    return 0;
}
