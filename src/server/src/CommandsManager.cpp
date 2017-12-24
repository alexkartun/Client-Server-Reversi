/*
 * CommandsManager.cpp
 */

#include "CommandsManager.h"
#include "StartCommand.h"
#include "GamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"

CommandsManager::CommandsManager(Server *server) {
	commandsMap["start"] = new StartCommand(server);
	commandsMap["list_games"] = new GamesCommand(server);
	commandsMap["join"] = new JoinCommand(server);
	commandsMap["play"] = new PlayCommand(server);
	commandsMap["close"] = new CloseCommand(server);
}

CommandsManager::~CommandsManager() {
	map<string, Command *>::iterator it;
	for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
		delete it->second;
	}
}

void CommandsManager::executeCommand(string command, vector<string> args, int client_socket) {
	Command *commandExecute = commandsMap[command];
	commandExecute->execute(args, client_socket);
}
