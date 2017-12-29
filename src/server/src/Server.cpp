/*
 * Server.cpp
 */
#include "Server.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server(int port): port(port), serverSocket(0) {
	lobby = new Lobby();
	cout << "Server" << endl;
}

Server::~Server() {
	delete lobby;
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
	listen(serverSocket, MAX_CONNECTED_CLIENTS); //TODO:check it
	lobby->startLobby(serverSocket);
}

int Server::getServerSocket() {
	return serverSocket;
}

void Server::closeServer() {
	lobby->closeConnectionWithClients();
	close(serverSocket);
}
