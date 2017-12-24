/*
 * JoinCommand.h
 */
#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_

#include "AbstractCommand.h"

class JoinCommand: public AbstractCommand {
public:
	JoinCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(vector<string> args, int client_socket) {
		string game_to_join = args.front();
		bool status = ref_to_server->joinGame(game_to_join);
		if (status) {
			string message = "You joined to this game '" + game_to_join + "'. Have Fun.";
			ref_to_server->writeToClient(client_socket, message.c_str());
			ref_to_server->activateGame(game_to_join, client_socket);
		} else {
			string message = "Can't join to this game '" + game_to_join + "'.";
			ref_to_server->writeToClient(client_socket, message.c_str());
		}
	}
};

#endif /* JOINCOMMAND_H_ */
