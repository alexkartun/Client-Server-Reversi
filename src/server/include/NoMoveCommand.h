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
	NoMoveCommand(Lobby *lobby): AbstractCommand(lobby) { }
	void execute(string args, int client_socket) {
		char buffer[LEN];
		memset(buffer, '\0', sizeof(buffer));
		strcpy(buffer, "NoMove");
		write(client_socket, buffer, LEN);  // send "noMove" to other player.
	}
};


#endif /* INCLUDE_NOMOVECOMMAND_H_ */
