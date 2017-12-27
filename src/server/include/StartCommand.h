/*
 * StartCommand.h
 */
#ifndef STARTCOMMAND_H_
#define STARTCOMMAND_H_

#include "AbstractCommand.h"

class StartCommand: public AbstractCommand {
public:
	StartCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(string args, int client_socket) {
		string message;
		string game_to_add = args; // game name.
		bool status = ref_to_server->addNewGame(game_to_add, client_socket);    // add new game to map.
		if (status) {															// only if status is true.
			message = "1";
			ref_to_server->writeToClient(client_socket, message.c_str());
			ref_to_server->updateSocketStatus(client_socket, waiting);    // update the status of player
		} else {														  // to waiting.
			message = "-1";
			ref_to_server->writeToClient(client_socket, message.c_str());
		}
	}
};

#endif /* STARTCOMMAND_H_ */
