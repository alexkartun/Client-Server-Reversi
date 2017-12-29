/*
 * Client.cpp
 */
#include "Client.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>

using namespace std;

Client::Client(char *serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort),
		clientSocket(0) {
	cout << "Client" << endl;
}

void Client::connectToServer() {
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		throw "Error opening socket";
	}
	// Convert the ip string to a network address
	struct in_addr address;
	if (!inet_aton(serverIP, &address)) {
		throw "Can't parse IP adress";
	}
	//Get a hostent structure for the given host adress
	struct hostent *server;
	server = gethostbyaddr((const void *) &address, sizeof(address), AF_INET);
	if (server == NULL) {
		throw "Host in unreachable";
	}
	// Create a structure for the server address
	struct sockaddr_in serverAdress;
	bzero((char *)&address, sizeof(address));

	serverAdress.sin_family = AF_INET;
	memcpy((char *) &serverAdress.sin_addr.s_addr, (char *)server->h_addr, server->h_length);

	// htons converts valurs between host and network byte orders
	serverAdress.sin_port = htons(serverPort);

	// establish a connection with the TCP server
	if (connect(clientSocket, (struct sockaddr *) &serverAdress, sizeof(serverAdress)) == -1) {
		throw "Error connecting to server";
	}
	cout << "Connected to server" << endl << endl;
}

void Client::readFromServer(char *buffer, int len) {
	// Read from server.
	int n = read(clientSocket, buffer, len);
	if (n == -1) {
		cout << "Error occured on reading from server." << endl;
	}
}

void Client::writeToServer(const char *buffer, int len) {
	// Write to server.
	int n = write(clientSocket, buffer, len);
	if (n == -1) {
		cout << "Error occured on writing to server." << endl;
	}
}

void Client::closeClient() {
	close(clientSocket);
}
