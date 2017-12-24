/*
 * main.cpp
 */
#include "Client.h"
#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#define SIZE 8
#define LEN 256
typedef enum result {failure, success} RESULT;
using namespace std;

// Sub-functions declaration.
RESULT checkInput(string, int*);
void runLocalGame(int);
RESULT runRemoteGame();

int main1() {
	string str_input;
	int input;

	cout << "Welcome to Reversi!" << endl << endl;
	cout << "Choose an opponent type:" <<endl;
	cout << "1. a human local player" <<endl;
	cout << "2. an AI player" <<endl;
	cout << "3. a remote player" <<endl;

	// Get and validate chosen mode from user.
	do {
		getline(cin, str_input);
		if (checkInput(str_input, &input) == success) {
			break;
		} else {
			cout << "Wrong input. Put input again!" << endl;
		}
	} while(true);

	switch (input) {
		case 1:
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
 * Validation of main user input.
 * User input should be a number between 1-3.
 * If so - store numeric value in &input and return SUCCESS.
 * Otherwise, return FAILURE.
 */
RESULT checkInput(string str_input, int* input) {
	if (str_input.length() == 1 && isdigit(str_input.at(0))) {
		*input = str_input.at(0) - '0';
		if (*input == 1 || *input == 2 || *input == 3) {
			return success;
		}
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
	config_client.open("src/client/client_config.txt");
	// Read IP and port from client configuration file.
	if (config_client.is_open()) {
		config_client >> ip;
		config_client >> port;
	} else {
		cout << "Failed to open file." << endl;
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
			cout << "Error occurred. Reason: " << msg << endl;
			return failure;
	}
	return success;
}
