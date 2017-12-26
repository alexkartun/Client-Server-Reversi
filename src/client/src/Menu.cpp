/*
 * Menu.cpp
 */

#include "Menu.h"

char buffer[LEN];

Menu::Menu() {
	commands.push_back("start <name>");
	commands.push_back("list_games");
	commands.push_back("join <name>");
}

void Menu::lobby() {
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

	switch (input) {
	case 1:
	case 2:
		runLocalGame(input);
		break;
	case 3:
		if (runRemoteGame() == failure) {
			exit(failure);
		}
		break;
	default:
		break;
	}
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
		if (pos != string::npos) {
			string command = str.substr(0, pos);
			if (!command.compare("start") || !command.compare("join")) {
				strcpy(buffer, str.c_str());
				break;
			}
		} else {
			if (!str.compare("list_games")) {
				strcpy(buffer, str.c_str());
				break;
			}
		}
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
	if (importClientDetailsFromFile(&port, ip) == failure) {
		return failure;
	}

	Client client(ip, port);
	try {
		client.connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason: " << msg << endl;
		return failure;
	}
	cout << "Commands you can use are:" << endl;
	displayCommands();
	string input;
	do {
		cout << "Type your command: ";
		getline(cin, input);
		checkCommand(input);
		string command(buffer);
		client.writeToServer(buffer, LEN);
		client.readFromServer(buffer, LEN);
		if (strcmp(buffer, "1") == 0) {
			cout << "Command executed successfully." << endl;
			string::size_type pos = command.find(' ', 0);
			command = command.substr(0, pos);
			if (command.compare("start") == 0) {
				cout << "Wait for other player to join" << endl;
			}
			break;
		}
		else if (strcmp(buffer, "-1") == 0) {
			cout << "Command failed. Try again." <<endl;
		} else {
			cout << buffer << endl;
		}
	} while(true);
	runGame(client);
	return success;
}

void Menu::runGame(Client client) {
	client.readFromServer(buffer, LEN);   //user got symbol.
	string playerData(buffer);
	//Parse symbol and game name.
	string::size_type pos = playerData.find(' ', 0);
	string symbol = playerData.substr(0, pos);
	string game = playerData.substr(pos + 1);

	Game reversi(SIZE, symbol.at(0), game);
	reversi.startGame();

	commands.clear();
	cout << "Comands u can use now are: " << endl;
	commands.push_back("<X> <Y>");
	commands.push_back("close <name>");
	displayCommands();
	cout << endl;

	if (symbol.at(0) == 'X') {
		reversi.playLocalTurn(buffer);
		client.writeToServer(buffer, LEN);
	}
	while (reversi.getStatus()) {
		cout << "Wait for other player to make move." <<endl;
		client.readFromServer(buffer, LEN);
	    if (strcmp(buffer, "close") == 0) {
	        break;
	    }
	    reversi.playRemoteTurn(buffer);
	    if (!reversi.getStatus()) { break; }
	    reversi.playLocalTurn(buffer);
	    if (strcmp(buffer, "end") == 0) { break; }
	    client.writeToServer(buffer, LEN);
	}
	playerData = "close " + game;
	if (strcmp(buffer, "close") == 0) {
		cout << "Other player disconnected. You win by technical win." << endl;
	} else if (strcmp(buffer, playerData.c_str()) == 0){
		cout << "Hope you enjoyed. Cya again!" << endl;
	} else {
		reversi.endGame();
	}
}
