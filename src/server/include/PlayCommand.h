/*
 * PlayCommand.h
 */
#ifndef PLAYCOMMAND_H_
#define PLAYCOMMAND_H_

#include "AbstractCommand.h"

class PlayCommand: public AbstractCommand {
public:
	PlayCommand(Lobby *lobby): AbstractCommand(lobby) { }
	void execute(string args, int client_socket) {
		char buffer[LEN];
		memset(buffer, '\0', sizeof(buffer));
		strcpy(buffer, args.c_str());
		write(client_socket, buffer, LEN);    // send move to other player.
	}
};

#endif /* PLAYCOMMAND_H_ */
