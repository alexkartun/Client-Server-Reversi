//============================================================================
// Name        : main.cpp
//============================================================================
#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main() {
	int port;
	ifstream config_client;
	config_client.open("src/server/server_config.txt");
	// Read port from config.
	if (config_client.is_open()) {
		config_client >> port;
	} else {
		cout << "Error occured on opening from file." << endl;
		exit(-1);
	}
	config_client.close();
	Server server(port);
	try {
		server.open();
	} catch (const char *msg) {
		cout << "Error occurred. Reason: " << msg << endl;
		exit(-1);
	}
	server.start();
	server.closeServer();
	exit(0);
}
