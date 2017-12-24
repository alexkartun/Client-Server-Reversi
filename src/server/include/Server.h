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

using namespace std;

class Server {
public:
	Server(int port);
	void open();
	void start();
	void closeServer();
	bool addNewGame(string game);
	bool joinGame(string game);
	vector<string> getNotActiveGames();
	void activateGame(string game, int socket_client);
	void stopGame(string game);
	void writeToClient(int socket_client, const char *message);
	void readFromClient(int socket_client, char *message);
	int getServerSocket();
	void insertClient(int);
	void addClientToGame(string, int);
	ClientsInGame getClientsOfGame(string);
private:
	int port;
	int serverSocket;
	vector<int> clients;
	map<string, bool> gamesInServer;
	map<string, ClientsInGame> gamesAndPlayers;
};

#endif /* SERVER_H_ */
