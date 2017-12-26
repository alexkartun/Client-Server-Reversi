/*
 * Server.h
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <vector>
#include <map>
#include <string>

struct ClientsInGame {
	int first_client;
	int second_client;
};

typedef enum status {chosing, waiting, playing, finished} STATUS;
using namespace std;

class Server {
public:
	Server(int port);
	void open();
	void start();
	int getServerSocket();
	void closeServer();
	int writeToClient(int socket_client, const char *message);
	int readFromClient(int socket_client, char *message);
	bool addNewGame(string game, int socket);
	bool joinGame(string game, int socket);
	void activateGame(string game);
	vector<string> getGamesOnHold();
	void cancelGameRoom(string gameName);
	void updateSocketStatus(int socket, STATUS status);
	STATUS socketStatus(int socket);
	void removeFinishedPlayers();
	void checkStatusSending(int status, string game, int socket);
private:
	int port;
	int serverSocket;
	vector<string> gamesOnHold;
	map<string, ClientsInGame> gamesAndPlayers;
	map<int, STATUS> sockets_status;
};

#endif /* SERVER_H_ */
