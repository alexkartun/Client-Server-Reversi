/*
 * StartCommand.h
 */
#ifndef STARTCOMMAND_H_
#define STARTCOMMAND_H_

#include "AbstractCommand.h"

class StartCommand: public AbstractCommand {
public:
	StartCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(vector<string> args, int client_socket) {
		string game_to_add = args.front();
		bool status = ref_to_server->addNewGame(game_to_add);
		if (status) {
			string message = "Game " + game_to_add + " is available. Wait for other player to join.";
						ref_to_server->writeToClient(client_socket, message.c_str());
			ref_to_server->addClientToGame(game_to_add, client_socket);
		} else {
			string message = "Game '" + game_to_add + "' is not available. Insert another one or join "
					+ "to available one.";
			ref_to_server->writeToClient(client_socket, message.c_str());
		}
	}
};

#endif /* STARTCOMMAND_H_ */
