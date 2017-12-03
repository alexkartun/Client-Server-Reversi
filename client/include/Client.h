/*
 * Client.h
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <string>
using namespace std;
class Client {
public:
	Client(const char *serverIP, int serverPort);
	void connectToServer();
	void sendExercise(char *, int);
	void settingPLayer(char *, int len) const;
	void waitForMove(char *, int len);
	void stop(char *, int);
private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* CLIENT_H_ */
