/*
 * NoMoveCommand.h
 *
 *  Created on: Dec 26, 2017
 *      Author: kartuna
 */

#ifndef INCLUDE_NOMOVECOMMAND_H_
#define INCLUDE_NOMOVECOMMAND_H_

#include "AbstractCommand.h"

class NoMoveCommand: public AbstractCommand {
public:
	NoMoveCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(string args, int client_socket) {
		ref_to_server->writeToClient(client_socket, "NoMove");   // send "noMove" to other player.
	}
};


#endif /* INCLUDE_NOMOVECOMMAND_H_ */
