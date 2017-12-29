/*
 * CommandsManager.h
 */

#include <map>
#include "Command.h"
#include "Lobby.h"

#ifndef COMMANDSMANAGER_H_
#define COMMANDSMANAGER_H_
/**
 * Command manager for execution of commands.
 */
class CommandsManager {
public:
	/**
	 * Constructor.
	 */
	CommandsManager(Lobby *lobby);
	/**
	 * Deconstructor.
	 */
	~CommandsManager();
	/**
	 * Execute command via map of commands.
	 */
	void executeCommand(string command, string args, int client_socket);
private:
	map <string, Command *> commandsMap;
};

#endif /* COMMANDSMANAGER_H_ */
