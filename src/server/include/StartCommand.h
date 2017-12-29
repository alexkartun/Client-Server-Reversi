/*
 * StartCommand.h
 */
#ifndef STARTCOMMAND_H_
#define STARTCOMMAND_H_

#include "AbstractCommand.h"

class StartCommand: public AbstractCommand {
public:
	StartCommand(Lobby *lobby): AbstractCommand(lobby) { }
	void execute(string args, int client_socket) {
		string message;
		string game_to_add = args; // game name.
		char buffer[LEN];
		memset(buffer, '\0', sizeof(buffer));
		bool status = lobby->addNewGame(game_to_add, client_socket);  // add new game to map.
		if (status) {													    // only if status is true.
			strcpy(buffer, "1");
			write(client_socket, buffer, LEN);
			lobby->updateSocketStatus(client_socket, waiting);    // update the status of player
		} else {														  // to waiting.
			strcpy(buffer, "-1");
			write(client_socket, buffer, LEN);
		}
	}
};

#endif /* STARTCOMMAND_H_ */
