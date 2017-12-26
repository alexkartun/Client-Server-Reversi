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
#define SIZE 4
#define LEN 256
typedef enum result {success, failure} RESULT;

using namespace std;

class Menu {
public:
	Menu();
	void lobby();
private:
	RESULT importClientDetailsFromFile(int *port, char *ip);
	void checkCommand(string command);
	RESULT checkInput(string, int*);
	void runLocalGame(int);
	RESULT runRemoteGame();
	void runGame(Client client);
	void displayCommands();
	vector<string> commands;
};

#endif /* MENU_H_ */
