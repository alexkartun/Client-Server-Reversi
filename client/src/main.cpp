/*
 * main.cpp
 */
#include "Client.h"
#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#define SIZE 4
#define LEN 256
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
		Game reversi(input, SIZE);
		reversi.startGame();
		//run the loop till end of the game
		while(reversi.getStatus()) {
			reversi.makeTurn();
		}
		reversi.endGame();
	// Input is 3 so want to play against remote player. So we need to open client.
	} else {
		Client client("127.0.0.1", 8000);
		char buffer[LEN];
		char player[LEN];
		try {
			client.connectToServer();
		} catch (const char *msg) {
			cout << "Failed to connect to server. Reason: " << msg << endl;
			exit(-1);
		}
		client.settingPLayer(player, LEN);
		Game reversi(SIZE, player);
		//run the loop till end of the game
		reversi.startGame();
		if (strcmp(player, "1") == 0) {
			while (reversi.getStatus()) {
				reversi.playLocalTurn(buffer);
				if (!reversi.getStatus()) {
					break;
				}
				client.sendExercise(buffer, LEN);
				client.waitForMove(buffer, LEN);
				if (strcmp(buffer, "End") == 0) {
					cout << "No possible moves for both players. Game is Over!" << endl;
					break;
				}
				reversi.playRemoteTurn(buffer);
			}
		} else {
			while(reversi.getStatus()) {
				client.waitForMove(buffer, LEN);
				if (strcmp(buffer, "End") == 0) {
					cout << "No possible moves for both players. Game is Over!" << endl;
					break;
				}
				reversi.playRemoteTurn(buffer);
				reversi.playLocalTurn(buffer);
				if (!reversi.getStatus()) {
					break;
				}
				client.sendExercise(buffer, LEN);
			}
		}
		reversi.endGame();
		strcpy(buffer, "End");
		client.stop(buffer, LEN);
	}
	return 0;
}
