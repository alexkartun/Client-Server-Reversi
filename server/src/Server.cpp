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

void Server::start() {
	// Create a socket point
	char buffer[LEN];
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		throw "Error opening socket";
	}
	// Assign a local adressto the socket
	struct sockaddr_in serverAdress;
	bzero((void *)&serverAdress, sizeof(serverAdress));
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_addr.s_addr = INADDR_ANY;
	serverAdress.sin_port = htons(port);
	if (bind(serverSocket, (struct sockaddr *) &serverAdress, sizeof(serverAdress)) == -1) {
		throw "Error on binding";
	}

	// Start listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);

	// Define the client socket's structures
	struct sockaddr_in first_clientAdress;
	socklen_t first_clientAdressLen;
	struct sockaddr_in second_clientAdress;
	socklen_t second_clientAdressLen;

	while (true) {
		cout << "Waiting to client connections..." << endl;

		// Accept a new client connection
		int clientSocket_first = accept(serverSocket, (struct sockaddr *) &first_clientAdress, &first_clientAdressLen);
		if (clientSocket_first == -1) {
			throw "Error on accept";
		}
		cout << "Client connected" << endl;
		strcpy(buffer, "first");
		write(clientSocket_first, buffer, LEN);
		int clientSocket_second = accept(serverSocket, (struct sockaddr *) &second_clientAdress, &second_clientAdressLen);
		if (clientSocket_second == -1) {
			throw "Error on accept";
		}
		cout << "Client connected" << endl;
		strcpy(buffer, "second");
		write(clientSocket_second, buffer, LEN);

		/////////////////////////////////////////////////////////////////////////////////////////////
		strcpy(buffer, "1");
		write(clientSocket_first, buffer, LEN);
		strcpy(buffer, "2");
		write(clientSocket_second, buffer, LEN);
		////////////////////////////////////////////////////////////////////////////////////////////
		while (true) {
			strcpy(buffer, "wait");
			write(clientSocket_second, buffer, LEN);
			handleClient(clientSocket_first, buffer);
			if (strcmp(buffer, "End") == 0) {
				write(clientSocket_second, buffer, LEN);
				break;
			}
			write(clientSocket_second, buffer, LEN);
			strcpy(buffer, "wait");
			write(clientSocket_first, buffer, LEN);
			handleClient(clientSocket_second, buffer);
			if (strcmp(buffer, "End") == 0) {
				write(clientSocket_first, buffer, LEN);
				break;
			}
			write(clientSocket_first, buffer, LEN);
		}

		// Close communication with the client
		close(clientSocket_first);
		close(clientSocket_second);
		break;
	}
}

void Server::stop() {
	close(serverSocket);
}

// Handle requests from a specific client
void Server::handleClient(int clientSocket, char *buffer) {
	int n = read(clientSocket, buffer, LEN);
	if (n == -1) {
		throw "Error on reading from client.";
	}
}
