/*
 * CloseCommand.h
 */

#ifndef CLOSECOMMAND_H_
#define CLOSECOMMAND_H_

#include "AbstractCommand.h"

class CloseCommand: public AbstractCommand {
public:
	CloseCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(vector<string> args, int client_socket) {
		string game_to_stop = args.front();
		ref_to_server->stopGame(game_to_stop);
	}
};

#endif /* CLOSECOMMAND_H_ */
