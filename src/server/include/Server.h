/*
 * Server.h
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <vector>
#include <map>
#include <string>
#include "Lobby.h"
#include <stdexcept>

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

/**
 * Server class.
 */
class Server {
public:
	/**
	 * Constructor.
	 */
	Server(int port);
	/**
	 * Deconstructor.
	 */
	~Server();
	/**
	 * Open server socket with binding.
	 */
	void open();
	/**
	 * Start listening to clients. Create main thread to listen.
	 */
	void start();
	/**
	 * Close server with suitable message to clients.
	 */
	void closeServer();
	/**
	 * Get server socket.
	 */
	int getServerSocket();
private:
	int port;
	int serverSocket;
	Lobby *lobby;
};

#endif /* SERVER_H_ */
