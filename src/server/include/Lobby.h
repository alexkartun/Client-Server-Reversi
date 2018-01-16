/*
 * Lobby.h
 */
#ifndef LOBBY_H_
#define LOBBY_H_

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include "ThreadPool.h"
#include "Task.h"
#define NUM_OF_THREADS 5

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
	/**
	 * Constructor.
	 */
	Lobby();
	/**
	 * Deconstructor.
	 */
	virtual ~Lobby();
	/**
	 * Start lobby.
	 */
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
	void cancelGameRoom(string gameName, int socket);
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
     * Add new task to pool and to list of tasks.
     */
    void addTask(Task *task) { pool->addTask(task); tasks.push_back(task); }
    /**
     * Get players that starting to play.
     */
    ClientsInGame getStartedClients(string gameName);
    /**
     * Get players that finished to play.
     */
    ClientsInGame getFinishedClients(string game_name, int client_socket);
    /**
     * Removed finished map from game.
     */
    void removeFinishedGame(string game_name, int socket_1, int socket_2);
    /**
     * Add player to map that joined to waiting game.
     */
    void joinPlayerToGame(string game_to_join, int client_socket);
private:
	vector<string> gamesOnHold;
	map<int, STATUS> sockets_status;
	multimap<string, ClientsInGame> gamesAndPlayers;
	ThreadPool *pool;
	vector<Task *> tasks;
};

#endif /* LOBBY_H_ */
