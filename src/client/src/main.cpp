/*
 * main.cpp
 */
#include "Client.h"
#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#define SIZE 4
#define LEN 256
typedef enum result {failure, success} RESULT;
using namespace std;

RESULT checkInput(string);
void runLocalGame(int);
RESULT runRemoteGame();

int main() {
	cout << "Welcome to Reversi!" << endl << endl;
	cout << "Choose an opponent type:" <<endl;
	cout << "1. a human local player" <<endl;
	cout << "2. an AI player" <<endl;
	cout << "3. a remote player" <<endl;

	// Choosing our mode and checking his validality.
	string str_input;
	int input;
	do {
		getline(cin, str_input);
		if (checkInput(str_input) == success) {
			// Converting char to int
			input = str_input.at(0) - 48;
			if (input == 1 || input == 2 || input == 3) {
				break;
			} else {
				cout << "Wrong input. Put input again!" << endl;
			}
		} else {
			cout << "Wrong input. Put input again!" << endl;
		}
	} while(true);

	switch (input) {
	case 1:
		runLocalGame(input);
		break;
	case 2:
		runLocalGame(input);
		break;
	case 3:
		if (runRemoteGame() == failure) {
			exit(-1);
		}
		break;
	default:
		break;
	}
	return 0;
}

/**
 * Check the validality of the input.
 */
RESULT checkInput(string str_input) {
	if (str_input.length() == 1 && isdigit(str_input.at(0))) {
		return success;
	}
	return failure;
}

/**
 * Run local game as: AI or a human local game.
 */
void runLocalGame(int input) {
	Game reversi(input, SIZE);
	reversi.startGame();
	while(reversi.getStatus()) {
		reversi.makeTurn();
	}
	reversi.endGame();
}

/**
 * Running the remote game.
 */
RESULT runRemoteGame() {
	string ip;
	int port;
	ifstream config_client;
	config_client.open("../../exe/client_config.txt");
	// Read from file ip and port.
	if (config_client.is_open()) {
		config_client >> ip;
		config_client >> port;
	} else {
		cout << "Failed on oppening the file." << endl;
		return failure;
	}
	config_client.close();
	Client client(ip.c_str(), port);
	char buffer[LEN];
	try {
		client.connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason: " << msg << endl;
		return failure;
	}
	try {
		// Waiting for server to set the players and update the players.
		client.waitForMove(buffer, LEN);
		Game reversi(SIZE, buffer[0]);
		// Start the game of both players after setting players order.
		reversi.startGame();
		if (strcmp(buffer, "1") == 0) {
			reversi.playLocalTurn(buffer);
			client.sendExercise(buffer, LEN);
		}
		while (reversi.getStatus()) {
			client.waitForMove(buffer, LEN);
			if (strcmp(buffer, "End") == 0) {
				break;
			}
			reversi.playRemoteTurn(buffer);
			reversi.playLocalTurn(buffer);
			client.sendExercise(buffer, LEN);
		}
		reversi.endGame();
		client.closeClient();
	} catch (const char *msg) {
			cout << "Error occured. Reason: " << msg << endl;
			return failure;
	}
	return success;
}
