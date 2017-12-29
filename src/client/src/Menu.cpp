/*
 * Menu.cpp
 */

#include "Menu.h"
#include <stdexcept>
#include <string>

// Global buffer we will use for sending and reading data from server.
char buffer[LEN];

Menu::Menu() {
	commands.push_back("start <name>");
	commands.push_back("list_games");
	commands.push_back("join <name>");
}

RESULT Menu::lobby() {
	// Print the options.
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
		// Converting char to int
		input = str_input.at(0) - 48;
		if (checkInput(str_input, &input) == success) {
			break;
		} else {
			cout << "Wrong input. Put input again!" << endl;
		}
	} while(true);
	// Switch table for user's input.
	switch (input) {
	case 1:
	case 2:
		runLocalGame(input);
		break;
	case 3:
		if (runRemoteGame() == failure) {
			return failure;
		}
		break;
	default:
		break;
	}
	return success;
}

/**
 * Check the validality of the input.
 */
RESULT Menu::checkInput(string str_input, int* input) {
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
void Menu::runLocalGame(int input) {
	Game reversi(input, SIZE);
	reversi.startGame();
	while(reversi.getStatus()) {
		reversi.makeTurn();
	}
	reversi.endGame();
}

/**
 * Import from file port and id for client.
 */
RESULT Menu::importClientDetailsFromFile(int *port, char *ip) {
	ifstream config_client;
	config_client.open("client_config.txt");
	// Read from file ip and port.
	if (config_client.is_open()) {
		config_client >> ip;
		config_client >> *port;
	} else {
		cout << "Failed on oppening the file." << endl;
		return failure;
	}
	config_client.close();
	return success;
}

/**
 * Display commands to user.
 */
void Menu::displayCommands() {
	for (unsigned int i = 0; i < commands.size(); i++) {
		cout << commands[i] << endl;
	}
}

void Menu::checkCommand(string str) {
	do {
		string::size_type pos = str.find(' ', 0);
		// Split the string by first space. If pos is npos so string is only one word, otherwise more.
		if (pos != string::npos) {
			string command = str.substr(0, pos);
			// Check if command is start or join. If yes update the buffer.
			if (!command.compare("start") || !command.compare("join")) {
				strcpy(buffer, str.c_str());
				break;
			}
		} else {
			// Check if command is "list_games". If yes update the buffer.
			if (!str.compare("list_games")) {
				strcpy(buffer, str.c_str());
				break;
			}
		}
		// Type again.
		cout << "Type your command again: ";
		getline(cin, str);
	} while (true);
}

/**
 * Running the remote game.
 */
RESULT Menu::runRemoteGame() {
	int port;
	char ip[LEN];
	// Import port and ip.
	if (importClientDetailsFromFile(&port, ip) == failure) {
		return failure;
	}

	Client *client = new Client(ip, port);
	// Connect to server.
	try {
		client->connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason: " << msg << endl;
		client->closeClient();
		delete client;
		return failure;
	}
	// Display commands user can make.
	cout << "Commands you can use are:" << endl;
	displayCommands();
	string input;
	do {
		cout << "Type your command: ";
		getline(cin, input);
		checkCommand(input);
		string command(buffer);    // After command was coosen validly save him on command for future use.
		client->writeToServer(buffer, LEN);
		client->readFromServer(buffer, LEN);
		if (strcmp(buffer, "1") == 0) {
			// If buffer is 1 meaning user wanted to start or join the game.
			cout << "Command executed successfully." << endl;
			string::size_type pos = command.find(' ', 0);
			command = command.substr(0, pos);
			// Here we using command we saved.
			if (command.compare("start") == 0) {
				cout << "Wait for other player to join" << endl;
			}
			break;
		}
		else if (strcmp(buffer, "-1") == 0) {
			// If buffer is "-1" meaning user wanted to start or join not valid game.
			cout << "Command failed. Try again." <<endl;
		} else if (strcmp(buffer, "exit") == 0){
			cout << "Server is closed. Come next time." << endl;  // meaning served is closed.
			return failure;
		} else {
			cout << buffer << endl;    // Otherwise print list of games.
		}
	} while(true);
	// Run game.
	runGame(client);
	client->closeClient();
	delete client;
	return success;
}

void Menu::runGame(Client *client) {
	client->readFromServer(buffer, LEN);   // User got symbol.

	string playerData(buffer);
	string::size_type pos = playerData.find(' ', 0);
	string symbol = playerData.substr(0, pos);    // Parse symbol.
	string game = playerData.substr(pos + 1);    // Parse game name.

	Game reversi(SIZE, symbol.at(0), game);
	reversi.startGame();

	commands.clear();    // Remove the old commands of user and insert new one.
	commands.push_back("<X> <Y>");
	commands.push_back("close <name>");
	cout << "Comands u can use now are: " << endl;
	displayCommands();    //Display the commands for user.
	cout << endl;

	if (symbol.at(0) == 'X') {    // If current client is 'X' meaning first player so start the flow.
		reversi.playLocalTurn(buffer);
		client->writeToServer(buffer, LEN);
	}
	while (reversi.getStatus()) {    //From here is same flow for both.
		cout << "Wait for other player to make move." <<endl;
		client->readFromServer(buffer, LEN);
	    if (strcmp(buffer, "close") == 0 || strcmp(buffer, "exit") == 0) {    // If user wanted to
	        break;															  //close game or server is closed.
	    }
	    reversi.updateRemoteTurn(buffer);    // Update remote move.
	    if (!reversi.getStatus()) { break; }    // If game is over break, or no possible moves for both players.
	    reversi.playLocalTurn(buffer);    //Play local turn with current client.
	    if (strcmp(buffer, "end") == 0) { break; }    //If board is full meaning end of the game, break.
	    client->writeToServer(buffer, LEN);
	}
	playerData = "close " + game;
	if (strcmp(buffer, "close") == 0) {    // If buffer was "close" so display for user this message.
		// Meaning other usre dced.
		cout << "Other player disconnected. You win by technical win." << endl;
	} else if (strcmp(buffer, playerData.c_str()) == 0){    // Print for user that closed the game.
		cout << "Hope you enjoyed. Cya again!" << endl;
	} else if (strcmp(buffer, "exit") == 0){
		cout << "Server is closed. Come next time." << endl;  // meaning served is closed.
	} else {
		reversi.endGame();    // End game.
	}
}
