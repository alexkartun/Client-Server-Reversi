/*
 * JoinCommand.h
 */
#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_

#include "AbstractCommand.h"

class JoinCommand: public AbstractCommand {
public:
	JoinCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(string args, int client_socket) {
		string game_to_join = args; // game name.
		bool status = ref_to_server->joinGame(game_to_join, client_socket);
		if (status) {
			string message = "1";
			ref_to_server->writeToClient(client_socket, message.c_str());
			ref_to_server->activateGame(game_to_join);
		} else {
			// If game is not found
			string message = "-1";
			ref_to_server->writeToClient(client_socket, message.c_str());
		}
	}
};

#endif /* JOINCOMMAND_H_ */
