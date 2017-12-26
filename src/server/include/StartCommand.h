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
		bool status = ref_to_server->addNewGame(game_to_add, client_socket);
		if (status) {
			message = "1";
			ref_to_server->writeToClient(client_socket, message.c_str());
			ref_to_server->updateSocketStatus(client_socket, waiting);
		} else {
			message = "-1";
			ref_to_server->writeToClient(client_socket, message.c_str());
		}
	}
};

#endif /* STARTCOMMAND_H_ */
