/*
 * Menu.h
 */

#ifndef MENU_H_
#define MENU_H_

#include "Client.h"
#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <cstring>
// Size of game.
#define SIZE 4
// Size of buffer.
#define LEN 256
// Status of function's.
typedef enum result {success, failure} RESULT;

using namespace std;

class Menu {
public:
	/*
	 * Constructor.
	 */
	Menu();
	/*
	 * Lobby of client by checking which game he want to play.
	 */
	RESULT lobby();
private:
	/**
	 * Import ip and port from file.
	 */
	RESULT importClientDetailsFromFile(int *port, char *ip);
	/**
	 * Check if command is valid if not insert again, update the buffer with valid command in the end,
	 */
	void checkCommand(string command);
	/**
	 * Check input of choosing the game user want to play.
	 */
	RESULT checkInput(string, int*);
	/*
	 * Run local game. Input 1: is user vs user and 2: is user vs cpy.
	 */
	void runLocalGame(int);
	/*
	 * Run remote game.
	 */
	RESULT runRemoteGame();
	/**
	 * After starting or joining the game we start to run the flow of the game.
	 */
	void runGame(Client *client);
	/**
	 * Display commands to user. Commands he can use.
	 */
	void displayCommands();
	/**
	 * Vector of all commands.
	 */
	vector<string> commands;
};

#endif /* MENU_H_ */
