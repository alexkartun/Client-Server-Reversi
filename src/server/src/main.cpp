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
		cout << "Error occured on opening from file." << endl;
		exit(failure);
	}
	config_server.close();

	Server *server = new Server(port);
	server->open();
	server->start();
	server->closeServer();

	exit(success);
}
