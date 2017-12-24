/*
 * main.cpp
 */
#include "Server.h"
#include "CommandsManager.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;

typedef enum result { success, failure } RESULT;

int main() {
	int port;
	ifstream config_server;
	config_server.open("server_config.txt");
	// Read port from config.
	if (config_server.is_open()) {
		config_server >> port;
	} else {
<<<<<<< HEAD
		cout << "Error occured on opening from file." << endl;
		exit(failure);
=======
		cout << "Error occurred while trying to open file." << endl;
		exit(-1);
	}
	config_client.close();
	Server server(port);
	try {
		server.open();
	} catch (const char *msg) {
		cout << "Error occurred. Reason: " << msg << endl;
		exit(-1);
>>>>>>> f7dd4f35a23b8075b1d5b56b198d084fd9d01d79
	}
	config_server.close();

	Server *server = new Server(port);
	server->open();
	server->start();
	server->closeServer();

	exit(success);
}
