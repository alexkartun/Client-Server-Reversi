/*
 * Lobby.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: kartuna
 */

#include "Lobby.h"
#include <algorithm>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "CommandsManager.h"

CommandsManager *command_manager;

void *listenToClients(void *);
void *handleClient(void *);
void execute(CommandsManager *mng, char* buffer, int socket);

struct ClientInfo {
	Lobby *lobby;
	int client_socket;
};

struct LobbyInfo {
	Lobby *lobby;
	int server_socket;
};

void Lobby::startLobby(int server_socket) {
	pthread_t main_thread;
	// Turn the main thread that accepting clients.
	LobbyInfo lobby_info;
	bzero((void *)&lobby_info, sizeof(lobby_info));

	lobby_info.lobby = this;
	lobby_info.server_socket = server_socket;

	CommandsManager manager(this);
	command_manager = &manager;

	int rc = pthread_create(&main_thread, NULL, listenToClients, &lobby_info);
	if (rc) {
		throw "Error on creating main thread.";
	}

	string input;
	do {    // type exit to close the server.
		getline(cin, input);
	} while (input.compare("exit") != 0);

	for (unsigned int i = 0; i < clients_threads.size(); i++) {    // cancel all threads
		pthread_cancel(clients_threads[i]);                    // and wait to them be closed.
		pthread_join(clients_threads[i], NULL);
	}

	pthread_cancel(main_thread);    //close main thread.
	pthread_join(main_thread, NULL);    // wait for him.
}

void *listenToClients(void *info) {
	LobbyInfo *lobby_info = (LobbyInfo *) info;

	Lobby *lobby = lobby_info->lobby;
	int server_socket = lobby_info->server_socket;

	struct sockaddr_in clientAddress;
	bzero((void *)&clientAddress, sizeof(clientAddress));
	socklen_t clientAdressLen;
	bzero((void *)&clientAdressLen, sizeof(clientAdressLen));

	ClientInfo client_info;
	bzero((void *)&client_info, sizeof(client_info));

	while (true) {
		cout << "Waiting to client connections..." << endl;
		// Accept a new client connection
		int client_socket = accept(server_socket, (struct sockaddr *) &clientAddress,
				&clientAdressLen);
		if (client_socket == -1) {
			cout << "Error on accept" << endl;
		}
		cout << "Client connected" << endl;

		pthread_t newClientThread;

		client_info.client_socket = client_socket;    // Insert client id to the struct.
		client_info.lobby = lobby;    // Insert the reference of lobby to struct.

		int rc = pthread_create(&newClientThread, NULL, handleClient, &client_info);
		if (rc) {
			throw "Error on creating client thread.";
		}
		lobby->addThread(newClientThread);
		lobby->removeFinishedPlayers();    // Remove players that finished to play.
	}
	return NULL;
}

void *handleClient(void *info) {
	ClientInfo *client_info = (ClientInfo *) info;

	Lobby *lobby = client_info->lobby;
	int client_socket = client_info->client_socket;

	char buffer[LEN];
	memset(buffer, '\0', sizeof(buffer));

	lobby->updateSocketStatus(client_socket, chosing);    // Update socket status to be choosing.

	while (lobby->socketStatus(client_socket) == chosing) {
		int status = read(client_socket, buffer, LEN);
		lobby->checkDisconnection(status, client_socket);
		if (lobby->socketStatus(client_socket) != chosing) { break; }
		execute(command_manager, buffer, client_socket); // Execute the command user want to execute.
	}
	return NULL;
}

void Lobby::removeFinishedPlayers() {
	map<int, STATUS>::iterator it;
	for (it = sockets_status.begin(); it != sockets_status.end(); it++) {
		if (it->second == finished) {
			sockets_status.erase(it->first);
		}
	}
}

void Lobby::checkDisconnection(int status, int socket) {
	if (status == 0) {
		updateSocketStatus(socket, finished);
		close(socket);
	}
}

STATUS Lobby::socketStatus(int socket) {
	return sockets_status[socket];
}

void Lobby::updateSocketStatus(int socket, STATUS status) {
	sockets_status[socket] = status;
}

void Lobby::checkStatusSending(int status, string gameName, int socket) {
	CommandsManager manager(this);
	if (status == 0) {
		string close = "close";
		manager.executeCommand(close, gameName, socket);
	}
}

vector<string> bufferParsing(char* buffer) {
	vector<string> argumentsVector;
	string str(buffer);
	string::size_type pos = str.find(' ', 0);
	if (pos != std::string::npos) {
		argumentsVector.push_back(str.substr(0, pos));
		argumentsVector.push_back(str.substr(pos + 1));
	} else {
		argumentsVector.push_back(str);
		argumentsVector.push_back("");
	}
	return argumentsVector;
}

void execute(CommandsManager *mng, char* buffer, int socket) {
	vector<string> arguments = bufferParsing(buffer);
	string command = arguments.front();
	arguments.erase(arguments.begin());
	string args = arguments.front();
	mng->executeCommand(command, args, socket);
	arguments.clear();
}

void Lobby::activateGame(string gameName) {
	int clientSocket1 = gamesAndPlayers[gameName].first_client;
	int clientSocket2 = gamesAndPlayers[gameName].second_client;
	updateSocketStatus(clientSocket1, playing);    //Status of both clients are playing.
	updateSocketStatus(clientSocket2, playing);

	int statusSending, statusReading;
	char buffer[LEN];
	memset(buffer, '\0', sizeof(buffer));

	string player =  "X " + gameName;
	strcpy(buffer, player.c_str());
	statusSending = write(clientSocket1, buffer, LEN);
	checkStatusSending(statusSending, gameName, clientSocket2);    // check if client is online.
	player =  "O " + gameName;
	strcpy(buffer, player.c_str());
	statusSending = write(clientSocket2, buffer, LEN);    // check if client is online.
	checkStatusSending(statusSending, gameName, clientSocket1);

	while (socketStatus(clientSocket1) == playing and socketStatus(clientSocket2) == playing) {
		statusReading = read(clientSocket1, buffer, LEN);
		checkStatusSending(statusReading, gameName, clientSocket2);    // check if client is online.
		if (socketStatus(clientSocket1) == finished and socketStatus(clientSocket2) == finished) {
			break;
		}
		execute(command_manager, buffer, clientSocket2);
		if (socketStatus(clientSocket1) == finished and socketStatus(clientSocket2) == finished) {
			break;
		}
		statusReading = read(clientSocket2, buffer, LEN);
		checkStatusSending(statusReading, gameName, clientSocket1);    // check if client is online.
		if (socketStatus(clientSocket1) == finished and socketStatus(clientSocket2) == finished) {
			break;
		}
		execute(command_manager, buffer, clientSocket1);
	}
}

void Lobby::cancelGameRoom(string gameName) {
	int client_socket1 = gamesAndPlayers[gameName].first_client;
	int client_socket2 = gamesAndPlayers[gameName].second_client;
	updateSocketStatus(client_socket1, finished);    // update status of both to finished.
	updateSocketStatus(client_socket2, finished);
	close(client_socket1);    // close both sockets.
	close(client_socket2);
	gamesAndPlayers.erase(gameName);    // cancel the room.
}

bool Lobby::addNewGame(string game_to_add, int client_socket) {
	// if "game_to_add" if found in gamesOnHold,
	// failed to open new game with similar name.
	if (find(gamesOnHold.begin(), gamesOnHold.end(), game_to_add)
			!= gamesOnHold.end()) {
		return false;
	}
	// Adds new game with unique name.
	else {
		gamesOnHold.push_back(game_to_add);
		ClientsInGame clients;
		clients.first_client = client_socket;
		gamesAndPlayers[game_to_add] = clients;
	}
	return true;
}

bool Lobby::joinGame(string game_to_join, int client_socket) {
	for (unsigned int i = 0; i < gamesOnHold.size(); i++) {
		// If chosen game is found in "gamesOnHold" vector,
		// remove it from games on hold.
		if (gamesOnHold[i].compare(game_to_join) == 0) {
			gamesOnHold.erase(gamesOnHold.begin() + i);
			gamesAndPlayers[game_to_join].second_client = client_socket;
			return true;
		}
	}
	return false;
}

vector<string> Lobby::getGamesOnHold() {
	return gamesOnHold;
}

void Lobby::closeConnectionWithClients() {
	map<int, STATUS>::iterator it;
	char buffer[LEN];
	memset(buffer, '\0', sizeof(buffer));
	strcpy(buffer, "exit");
	for (it = sockets_status.begin(); it != sockets_status.end(); it++) {
		write(it->first, buffer, LEN);
		close(it->first);
	}
}
