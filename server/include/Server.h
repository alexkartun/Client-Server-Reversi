/*
 * Server.h
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <string>
using namespace std;

class Server {
public:
	Server(int port);
	void open();
	void start();
	void closeServer();

private:
	int port;
	int serverSocket;
	void runProcess(int socket_1, int socket_2);
	void readFromClient(int clientSocket, char *buffer);
	void writeToClient(int clientSocket, char *buffer);
};

#endif /* SERVER_H_ */
