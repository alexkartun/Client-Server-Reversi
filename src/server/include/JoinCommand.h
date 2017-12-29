/*
 * JoinCommand.h
 */
#ifndef JOINCOMMAND_H_
#define JOINCOMMAND_H_

#include "AbstractCommand.h"

class JoinCommand: public AbstractCommand {
public:
	JoinCommand(Lobby *lobby): AbstractCommand(lobby) { }
	void execute(string args, int client_socket) {
		string game_to_join = args; // game name.
		char buffer[LEN];
		memset(buffer, '\0', sizeof(buffer));
		bool status = lobby->joinGame(game_to_join, client_socket);
		if (status) {    // check if can join the game.
			strcpy(buffer, "1");
			write(client_socket, buffer, LEN);
			lobby->activateGame(game_to_join);    // if can join activate game with both clients.
		} else {    // If game is not found
			strcpy(buffer, "-1");
			write(client_socket, buffer, LEN);
		}
	}
};

#endif /* JOINCOMMAND_H_ */
