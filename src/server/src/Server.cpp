/*
 * Server.cpp
 */
#include "Server.h"
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;
#define MAX_CONNECTED_CLIENTS 2
#define LEN 256

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
	char buffer[LEN];
    memset(buffer, 0, sizeof(buffer));
	// Start listening to incoming connections.
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
	// Define the client socket's structures
	struct sockaddr_in first_clientAdress;
    bzero((void *)&first_clientAdress, sizeof(first_clientAdress));
	socklen_t first_clientAdressLen;
    bzero((void *)&first_clientAdressLen, sizeof(first_clientAdressLen));
	struct sockaddr_in second_clientAdress;
    bzero((void *)&second_clientAdress, sizeof(second_clientAdress));
	socklen_t second_clientAdressLen;
    bzero((void *)&second_clientAdressLen, sizeof(second_clientAdressLen));
	// Handle error occured on inner while.
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
				cout << "Error occured. Reason: " << msg << endl;
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
				cout << "Error occured. Reason: " << msg << endl;
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
		}
	}
}

void Server::runProcess(int firstClientSocket, int secondClientSocket) {
	char buffer[LEN];
	cout << "Both users connected starting the game." << endl;
	while(true) {
		readFromClient(firstClientSocket, buffer);
		if (!strcmp(buffer, "End")) {
			writeToClient(secondClientSocket, buffer);
			break;
		}
		writeToClient(secondClientSocket, buffer);
		strcpy(buffer, "wait");
		writeToClient(firstClientSocket, buffer);
		readFromClient(secondClientSocket, buffer);
		if (!strcmp(buffer, "End")) {
			writeToClient(firstClientSocket, buffer);
			break;
		}
		writeToClient(firstClientSocket, buffer);
		strcpy(buffer, "wait");
		writeToClient(secondClientSocket, buffer);
	}
}

void Server::writeToClient(int clientSocket, char *buffer) {
	int n = write(clientSocket, buffer, LEN);
	if (n == -1) {
		throw "Error on writing to client.";
	}
	if (n == 0) {
		throw "User disconnected.";
	}
}

void Server::readFromClient(int clientSocket, char *buffer) {
	int n = read(clientSocket, buffer, LEN);
	if (n == -1) {
		throw "Error on reading from client.";
	}
	if (n == 0) {
		throw "User disconnected.";
	}
}

void Server::closeServer() {
	close(serverSocket);
}
