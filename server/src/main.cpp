//============================================================================
// Name        : main.cpp
//============================================================================
#include "Server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main12() {
	Server server(8000);
	try {
		server.open();
	} catch (const char *msg) {
		cout << "Error occurred. Reason: " << msg << endl;
		exit(-1);
	}
	try {
		server.start();
	} catch (const char *msg) {
		cout << "Error occurred. Reason: " << msg << endl;
		server.closeServer();
		exit(-1);
	}
	server.closeServer();
	exit(0);
}
