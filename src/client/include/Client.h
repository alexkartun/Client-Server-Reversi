/*
 * Client.h
 */
#ifndef CLIENT_H_
#define CLIENT_H_
#include <string>

using namespace std;
class Client {
public:
	/**
	 * Constructor.
	 */
	Client(char *serverIP, int serverPort);
	/**
	 * Connect to server.
	 */
	void connectToServer();
	/**
	 * Send msg to server.
	 */
	void readFromServer(char *, int);
	/**
	 * Read msg from server.
	 */
	void writeToServer(const char *, int len);
	/**
	 * Close clien socket.
	 */
	void closeClient();
private:
	char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* CLIENT_H_ */
