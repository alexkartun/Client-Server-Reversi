/*
 * PlayCommand.h
 */
#ifndef PLAYCOMMAND_H_
#define PLAYCOMMAND_H_

#include "AbstractCommand.h"

class PlayCommand: public AbstractCommand {
public:
	PlayCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(string args, int client_socket) {
		ref_to_server->writeToClient(client_socket, args.c_str()); // <X> <Y>
	}
};

#endif /* PLAYCOMMAND_H_ */
