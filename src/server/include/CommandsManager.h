/*
 * CommandsManager.h
 */

#include <map>
#include "Command.h"
#include "Server.h"

#ifndef COMMANDSMANAGER_H_
#define COMMANDSMANAGER_H_

class CommandsManager {
public:
	CommandsManager(Server *server);
	~CommandsManager();
	/**
	 * Execute command via map of commands.
	 */
	void executeCommand(string command, string args, int client_socket);
private:
	map <string, Command *> commandsMap;
};

#endif /* COMMANDSMANAGER_H_ */
