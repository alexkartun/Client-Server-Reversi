/*
 * CloseCommand.h
 */

#ifndef CLOSECOMMAND_H_
#define CLOSECOMMAND_H_

#include "AbstractCommand.h"

class CloseCommand: public AbstractCommand {
public:
	CloseCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(string args, int client_socket) {
		string game_to_stop = args; // game name;
		ref_to_server->writeToClient(client_socket, "close");    // write to client "close"
		ref_to_server->cancelGameRoom(game_to_stop);    // cancel the room.
	}
};

#endif /* CLOSECOMMAND_H_ */
