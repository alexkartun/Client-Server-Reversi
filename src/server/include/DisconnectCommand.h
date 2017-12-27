/*
 * DisconnectCommand.h
 */

#ifndef SRC_DISCONNECTCOMMAND_H_
#define SRC_DISCONNECTCOMMAND_H_

#include "AbstractCommand.h"

class DisconnectCommand: public AbstractCommand {
public:
	DisconnectCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(string args, int client_socket) {
		string game_to_stop = args; // game name;
		ref_to_server->writeToClient(client_socket, "-1");
		ref_to_server->cancelGameRoom(game_to_stop);
	}
};

#endif /* SRC_DISCONNECTCOMMAND_H_ */
