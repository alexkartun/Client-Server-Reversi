/*
 * Lobby.h
 */
#ifndef LOBBY_H_
#define LOBBY_H_

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

struct ClientsInGame {
	int first_client;
	int second_client;
};

using namespace std;
typedef enum status {chosing, waiting, playing, finished} STATUS;
#define LEN 256
/**
 * Lobby of handling clients and starting games.
 */
class Lobby {
public:
	Lobby() { }
	/**
	 * Start lobby.
	 */
	~Lobby() { }
	void startLobby(int server_socket);
	/**
	 * Checking status of sending message to client. Care about dces.
	 */
    void checkStatusSending(int status, string game, int socket);
    /**
     * Update socket status of client.
	 */
    void updateSocketStatus(int socket, STATUS status);
	/**
     * Get socket status.
	 */
	STATUS socketStatus(int socket);
	/**
	 * Cancel game room. Meaning remove game from map.
	 */
	void cancelGameRoom(string gameName);
	/**
	 * Get list of games that on hold.
	 */
	vector<string> getGamesOnHold();
	/**
	 * Add new game to map.
	 */
	bool addNewGame(string game, int socket);
	/**
	 * Add socket of second player to map.
	 */
    bool joinGame(string game, int socket);
    /**
	 * Activate game. Start running the game between two clients.
	 */
	void activateGame(string game);
	/**
	 * Removed clients that finished to play.
	 */
	void removeFinishedPlayers();
	/**
	 * checkDisconection of client in lobby.
	 */
    void checkDisconnection(int status, int socket);
	/**
	 * Close all client sockets, server shuted down.
	 */
    void closeConnectionWithClients();
    /**
     * Add thread to vector of threads.
     */
    void addThread(pthread_t thread) { clients_threads.push_back(thread); }
private:
	vector<string> gamesOnHold;
	map<int, STATUS> sockets_status;
	map<string, ClientsInGame> gamesAndPlayers;
	vector<pthread_t> clients_threads;
};

#endif /* LOBBY_H_ */
