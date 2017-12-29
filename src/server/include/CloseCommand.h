/*
 * CloseCommand.h
 */

#ifndef CLOSECOMMAND_H_
#define CLOSECOMMAND_H_

#include "AbstractCommand.h"

class CloseCommand: public AbstractCommand {
public:
	CloseCommand(Lobby *lobby): AbstractCommand(lobby) { }
	void execute(string args, int client_socket) {
		string game_to_stop = args; // game name;
		char buffer[LEN];
		memset(buffer, '\0', sizeof(buffer));
		strcpy(buffer, "close");
		write(client_socket, buffer, LEN);    // write to client "close"
		lobby->cancelGameRoom(game_to_stop);    // cancel the room.
	}
};

#endif /* CLOSECOMMAND_H_ */
