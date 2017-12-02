/*
 * main.cpp
 */
#include "Client.h"
#include "Game.h"
#include <iostream>
#include <stdlib.h>
#define SIZE 8
using namespace std;

int main() {
	cout << "Welcome to Reversi!" << endl << endl;
	string str_input;
	int input;
	cout << "Choose an opponent type:" <<endl;
	cout << "1. a human local player" <<endl;
	cout << "2. an AI player" <<endl;
	cout << "3. a remote player" <<endl;
	// Choosing our mode.
	do {
		getline(cin, str_input);
		if (str_input.length() == 1 && isdigit(str_input.at(0))) {
			input = str_input.at(0) - 48;
			if (input == 1) {
				break;
			} else if (input == 2) {
				break;
			} else if (input == 3) {
				break;
			} else {
				cout << "Wrong input." << endl;
			}
		} else {
			cout << "Wrong input." << endl;
		}
	} while(true);
	// After we choose whom we want to play we running the Game.
	// If input is 1 or 2 so we dont need to run the game via server. So we will do it regular like we did
	// on previous exercises.
	if (input == 1 || input == 2) {
		Game reversi(input);
		reversi.initGame(SIZE);
		reversi.startGame();
		//run the loop till end of the game
		while(reversi.getStatus()) {
			reversi.playTurn();
		}
		reversi.endGame();
	// Input is 3 so want to play against remote player. So we need to open client.
	} else {
		Client client("127.0.0.1", 5000);
		try {
			client.connectToServer();
		} catch (const char *msg) {
			cout << "Failed to connect to server. Reason: " << msg << endl;
			exit(-1);
		}
		string player;
		while (true) {
			//player = client.whichPlayer();
		}
	}
	return 0;
}
