/*
 * Client.h
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <string.h>
class Client {
public:
	Client(const char *serverIP, int serverPort);
	void connectToServer();
	void sendExercise(int row, int col);
	//string whichPlayer();
private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* CLIENT_H_ */
