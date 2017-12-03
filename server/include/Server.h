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
	void start();
	void stop();

private:
	int port;
	int serverSocket;

	void handleClient(int clientSocket, char *);
};

#endif /* SERVER_H_ */
