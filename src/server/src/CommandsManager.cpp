/*
 * CommandsManager.cpp
 */

#include "CommandsManager.h"
#include "StartCommand.h"
#include "GamesCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"
#include "NoMoveCommand.h"

CommandsManager::CommandsManager(Lobby *lobby) {
	commandsMap["start"] = new StartCommand(lobby);
	commandsMap["list_games"] = new GamesCommand(lobby);
	commandsMap["join"] = new JoinCommand(lobby);
	commandsMap["play"] = new PlayCommand(lobby);
	commandsMap["close"] = new CloseCommand(lobby);
	commandsMap["NoMove"] = new NoMoveCommand(lobby);
}

CommandsManager::~CommandsManager() {
	map<string, Command *>::iterator it;
	for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
		delete it->second;
	}
}

void CommandsManager::executeCommand(string command, string args, int client_socket) {
	Command *commandExecute = commandsMap[command];
	commandExecute->execute(args, client_socket);
}
