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
	CommandsManager *manager;
	Server *server;
	int client_socket;
};

void *listenToClients(void *);
void *handleClient(void *);
vector<string> bufferParsing(char* buffer);
void execute(Server *srvr, CommandsManager *mng, char* buffer, int socket);

Server::Server(int port): port(port), serverSocket(0) {
	cout << "Server" << endl;
}

void Server::open() {
	// Create a socket point.
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		throw "Error opening socket";
	}
	// Assign a local address to the socket.
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

	vector<pthread_t> client_threads;
	ClientInfo client_info;

	CommandsManager manager(server);
	while (true) {
		cout << "Waiting to client connections..." << endl;
		// Accept a new client connection
		int client_socket = accept(server->getServerSocket(), (struct sockaddr *) &clientAdress,
				&clientAdressLen);
		if (client_socket == -1) {
			throw "Error on accept";
		}
		cout << "Client connected" << endl;

		client_info.client_socket = client_socket;
		client_info.server = server;
		client_info.manager = &manager;

		pthread_t newClientThread;
		client_threads.push_back(newClientThread);
		int rc = pthread_create(&newClientThread, NULL, handleClient, &client_info);
		if (rc) {
			throw "Error on creating client thread.";
		}
		server->removeFinishedPlayers();
	}
}

void Server::removeFinishedPlayers() {
	map<int, STATUS>::iterator it;
	for (it = sockets_status.begin(); it != sockets_status.end(); it++) {
		if (it->second == finished) {
			sockets_status.erase(it->first);
		}
	}

}

// info = server + socket.
void *handleClient(void *info) {
	ClientInfo *client_info = (ClientInfo *) info;
	Server *server = client_info->server;
	int client_socket = client_info->client_socket;
    server->updateSocketStatus(client_socket, chosing);
	CommandsManager *manager = client_info->manager;
	server->updateSocketStatus(client_socket, chosing);    //update socket status to be true

	char buffer[LEN];
	while (server->socketStatus(client_socket) == chosing) {
		server->readFromClient(client_socket, buffer);
		execute(server, manager, buffer, client_socket);
	}
	return NULL;
}

STATUS Server::socketStatus(int socket) {
	return sockets_status[socket];
}

void Server::updateSocketStatus(int socket, STATUS status) {
	sockets_status[socket] = status;
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

void execute(Server *srvr, CommandsManager *mng, char* buffer, int socket) {
	vector<string> arguments = bufferParsing(buffer);
	string command = arguments.front();
	arguments.erase(arguments.begin());
	string args = arguments.front();
	mng->executeCommand(command, args, socket);
	arguments.clear();
}

void Server::checkStatusSending(int status, string gameName, int socket) {
	CommandsManager manager(this);
	if (status == 0) {
		string disconnect = "close";
		manager.executeCommand(disconnect, gameName, socket);
	}
}

void Server::activateGame(string gameName) {
	int clientSocket1 = gamesAndPlayers[gameName].first_client;
	int clientSocket2 = gamesAndPlayers[gameName].second_client;
	updateSocketStatus(clientSocket1, playing);
	updateSocketStatus(clientSocket2, playing);
	char buffer[LEN];
	int statusSending, statusReading;
	CommandsManager manager(this);
	string player =  "X " + gameName;
	strcpy(buffer, player.c_str());
	statusSending = writeToClient(clientSocket1, buffer);
	checkStatusSending(statusSending, gameName, clientSocket2);
	player =  "O " + gameName;
	strcpy(buffer, player.c_str());
	statusSending = writeToClient(clientSocket2, buffer);
	checkStatusSending(statusSending, gameName, clientSocket1);
	while (socketStatus(clientSocket1) == playing and socketStatus(clientSocket2) == playing) {
		statusReading = readFromClient(clientSocket1, buffer);
		checkStatusSending(statusReading, gameName, clientSocket2);
		if (socketStatus(clientSocket1) == finished and socketStatus(clientSocket2) == finished) {
			break;
		}
		execute(this, &manager, buffer, clientSocket2);
		if (socketStatus(clientSocket1) == finished and socketStatus(clientSocket2) == finished) {
			break;
		}
		statusReading = readFromClient(clientSocket2, buffer);
		checkStatusSending(statusReading, gameName, clientSocket1);
		if (socketStatus(clientSocket1) == finished and socketStatus(clientSocket2) == finished) {
			break;
		}
		execute(this, &manager, buffer, clientSocket1);
	}
}

int Server::getServerSocket() {
	return serverSocket;
}

void Server::cancelGameRoom(string gameName) {
	int client_socket1 = gamesAndPlayers[gameName].first_client;
	int client_socket2 = gamesAndPlayers[gameName].second_client;
	updateSocketStatus(client_socket1, finished);
	updateSocketStatus(client_socket2, finished);
	close(client_socket1);
	close(client_socket2);
	gamesAndPlayers.erase(gameName);
}

bool Server::addNewGame(string game_to_add, int client_socket) {
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

bool Server::joinGame(string game_to_join, int client_socket) {
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

vector<string> Server::getGamesOnHold() {
	return gamesOnHold;
}

int Server::writeToClient(int socket_client, const char *message) {
	int n = write(socket_client, message, LEN);
	if (n == -1) {
		cout << "Error occurred. Write to client!" << endl;
	}
	if (n == 0) {
		cout << "User disconnected." << endl;
	}
	return n;
}

int Server::readFromClient(int socket_client, char *message) {
	int n = read(socket_client, message, LEN);
	if (n == -1) {
		cout << "Error occurred. Read from client!" << endl;
	}
	if (n == 0) {
		cout << "User disconnected." << endl;
	}
	return n;
}

void Server::closeServer() {
	close(serverSocket);
}
