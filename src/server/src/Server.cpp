/*
 * Server.cpp
 */
#include "Server.h"
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "CommandsManager.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 10
#define LEN 256

struct ClientInfo {
	Server *server;
	int client_socket;
};

struct SessionInfo {
	Server *server;
	string game;
};

void *listenToClients(void *);
void *handleClient(void *);
void *RunSession(void *);

Server::Server(int port): port(port), serverSocket(0) {
	cout << "Server" << endl;
}

void Server::open() {
	// Create a socket point.
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		throw "Error opening socket";
	}
	// Assign a local adressto the socket.
	struct sockaddr_in serverAdress;
	bzero((void *)&serverAdress, sizeof(serverAdress));
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_addr.s_addr = INADDR_ANY;
	serverAdress.sin_port = htons(port);
	// Bind the server to port.
	if (bind(serverSocket, (struct sockaddr *) &serverAdress, sizeof(serverAdress)) == -1) {
		throw "Error on binding";
	}
}

void Server::start() {
	// Start listening to incoming connections.
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
<<<<<<< HEAD
	// Define the client socket's structures
	struct sockaddr_in first_clientAdress;
    bzero((void *)&first_clientAdress, sizeof(first_clientAdress));
	socklen_t first_clientAdressLen;
    bzero((void *)&first_clientAdressLen, sizeof(first_clientAdressLen));
	struct sockaddr_in second_clientAdress;
    bzero((void *)&second_clientAdress, sizeof(second_clientAdress));
	socklen_t second_clientAdressLen;
    bzero((void *)&second_clientAdressLen, sizeof(second_clientAdressLen));
	// Handle error occurred on inner while.
	while (true) {
		// Server start his processes by listening and handle clients.
		while (true) {
			cout << "Waiting to client connections..." << endl;
			// Accept a new client connection
			int clientSocket_first = accept(serverSocket, (struct sockaddr *) &first_clientAdress,
				&first_clientAdressLen);
			if (clientSocket_first == -1) {
				cout << "Error on accept" << endl;
				break;
			}
			cout << "Client connected" << endl;
			// First client need to wait.
			strcpy(buffer, "first");
			try {
				writeToClient(clientSocket_first, buffer);
			} catch (const char *msg) {
				cout << "Error occurred. Reason: " << msg << endl;
				close(clientSocket_first);
				break;
			}
			int clientSocket_second = accept(serverSocket, (struct sockaddr *) &second_clientAdress,
					&second_clientAdressLen);
			if (clientSocket_second == -1) {
				cout << "Error on accept" << endl;
				close(clientSocket_second);
				break;
			}
			cout << "Client connected" << endl;
			// Setting the players value.
			try {
				strcpy(buffer, "1");
				writeToClient(clientSocket_first, buffer);
				strcpy(buffer, "2");
				writeToClient(clientSocket_second, buffer);
			} catch (const char *msg) {
				cout << "Error occurred. Reason: " << msg << endl;
				close(clientSocket_first);
				close(clientSocket_second);
				break;
			}
			// Start the process of the game.
			try {
				runProcess(clientSocket_first, clientSocket_second);
			} catch(const char *msg) {
				cout << "Error occured. Reason: " << msg << endl;
			}
			// Close communication with the client.
			close(clientSocket_first);
			close(clientSocket_second);
			cout << "Session finished." << endl;
=======

	pthread_t main_thread;
	int rc = pthread_create(&main_thread, NULL, listenToClients, this);
	if (rc) {
		throw "Error on creating main thread.";
	}
	pthread_exit(NULL);
}

void *listenToClients(void *serv) {
	Server *server = (Server *) serv;

	struct sockaddr_in clientAdress;
	bzero((void *)&clientAdress, sizeof(clientAdress));
	socklen_t clientAdressLen;
	bzero((void *)&clientAdressLen, sizeof(clientAdressLen));

	pthread_t threads[MAX_CONNECTED_CLIENTS];
	ClientInfo client_info;
	for (int i = 0; i < MAX_CONNECTED_CLIENTS; i++) {
		cout << "Waiting to client connections..." << endl;
		// Accept a new client connection
		int client_socket = accept(server->getServerSocket(), (struct sockaddr *) &clientAdress,
				&clientAdressLen);
		if (client_socket == -1) {
			throw "Error on accept";
		}
		cout << "Client connected" << endl;
		server->insertClient(client_socket);
		client_info.client_socket = client_socket;
		client_info.server = server;
		int rc = pthread_create(&threads[i], NULL, handleClient, &client_info);
		if (rc) {
			throw "Error on creating client thread.";
>>>>>>> 51732a94ec53d66850a35964bbb37db97d047275
		}
	}
	return NULL;
}

void *handleClient(void *info) {
	ClientInfo *client_info = (ClientInfo *) info;
	CommandsManager manager(client_info->server);
	char buffer[LEN];
	while (true) {
		client_info->server->readFromClient(client_info->client_socket, buffer);
		char *parser = strtok(buffer, " ");
		vector<string> arguments;
		while (parser) {
			string argument(parser);
			arguments.push_back(argument);
			parser = strtok(NULL, " ");
		}
		string command = arguments.front();
		arguments.erase(arguments.begin());

		manager.executeCommand(command, arguments, client_info->client_socket);
		arguments.clear();
	}
	return NULL;
}

void Server::insertClient(int client_socket) {
	clients.push_back(client_socket);
}

int Server::getServerSocket() {
	return serverSocket;
}

bool Server::addNewGame(string game_to_add) {
	if (gamesInServer.find(game_to_add) == gamesInServer.end()) {
		gamesInServer[game_to_add] = false;
		return true;
	}
	return false;
}

bool Server::joinGame(string game_to_join) {
	map<string, bool>::iterator it;
	for (it = gamesInServer.begin(); it != gamesInServer.end(); it++) {
		if (it->first == game_to_join and it->second == false) {
			return true;
		}
	}
	return false;
}

void Server::addClientToGame(string game, int client_socket) {
	ClientsInGame clients;
	clients.first_client = client_socket;
	gamesAndPlayers[game] = clients;
}

void Server::activateGame(string game_to_activate, int client_socket) {
	gamesInServer[game_to_activate] = true;
	ClientsInGame clients = gamesAndPlayers[game_to_activate];
	clients.second_client = client_socket;
	gamesAndPlayers[game_to_activate] = clients;
	pthread_t session_thread;
	SessionInfo session_info;
	session_info.server = this;
	session_info.game = game_to_activate;
	int rc = pthread_create(&session_thread, NULL, RunSession, &session_info);
	if (rc) {
		throw "Error on creating session thread.";
	}
	while (true) {
		if (!gamesInServer[game_to_activate]) {
			break;
		}
	}
}


void *RunSession(void *info) {
	SessionInfo *session_info = (SessionInfo *) info;
	Server *server = session_info->server;
	ClientsInGame clients = server->getClientsOfGame(session_info->game);
	CommandsManager manager(server);
	char buffer[LEN];
	strcpy(buffer, "X");
	server->writeToClient(clients.first_client, buffer);
	strcpy(buffer, "O");
	server->writeToClient(clients.second_client, buffer);

	while (true) {
		server->readFromClient(clients.first_client, buffer);

		server->writeToClient(clients.second_client, buffer);
		server->readFromClient(clients.second_client, buffer);
		server->writeToClient(clients.first_client, buffer);
	}

	return NULL;
}

ClientsInGame Server::getClientsOfGame(string game) {
	return gamesAndPlayers[game];
}

void Server::stopGame(string game_to_stop) {
	gamesInServer.erase(game_to_stop);
}

vector<string> Server::getNotActiveGames() {
	vector<string> listGames;
	map<string, bool>::iterator it;
	for (it = gamesInServer.begin(); it != gamesInServer.end(); it++) {
		if (it->second == false) {
			listGames.push_back(it->first);
		}
	}
	return listGames;
}

void Server::writeToClient(int socket_client, const char *message) {
	int n = write(socket_client, message, LEN);
	if (n == -1) {
		cout << "Error occured. Write to client!" << endl;
	}
	if (n == 0) {
		cout << "User disconnected." << endl;
	}
}

void Server::readFromClient(int socket_client, char *message) {
	int n = read(socket_client, message, LEN);
	if (n == -1) {
		cout << "Error occured. Read from client!" << endl;
	}
	if (n == 0) {
		cout << "User disconnected." << endl;
	}
}

void Server::closeServer() {
	close(serverSocket);
}
