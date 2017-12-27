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
	Client(const char *serverIP, int serverPort);
	/**
	 * Connect to server.
	 */
	void connectToServer();
	/**
	 * Send msg to server.
	 */
	int readFromServer(char *, int);
	/**
	 * Read msg from server.
	 */
	int writeToServer(const char *, int len);
	/**
	 * Close clien socket.
	 */
	void closeClient();
private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* CLIENT_H_ */
