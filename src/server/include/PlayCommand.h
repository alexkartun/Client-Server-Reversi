/*
 * PlayCommand.h
 */
#ifndef PLAYCOMMAND_H_
#define PLAYCOMMAND_H_

#include "AbstractCommand.h"

class PlayCommand: public AbstractCommand {
public:
	PlayCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(vector<string> args, int client_socket) { }
};

#endif /* PLAYCOMMAND_H_ */
