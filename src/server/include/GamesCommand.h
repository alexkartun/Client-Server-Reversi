/*
 * GamesCommand.h
 */

#ifndef GAMESCOMMAND_H_
#define GAMESCOMMAND_H_

#include "AbstractCommand.h"

class GamesCommand: public AbstractCommand {
public:
	GamesCommand(Lobby *lobby): AbstractCommand(lobby) { }
	void execute(string args, int client_socket) {
		vector<string> list_of_games = lobby->getGamesOnHold();   // get list of games.
		string list_to_string = "Active games on hold:";
		if (list_of_games.empty()) {    // if list is empty send to client "none"
			list_to_string += " None!";
		} else {    // otherwise send him representation of all games on hold.
			for (unsigned int i = 0; i < list_of_games.size(); i++) {
				if (i == 0) {
					list_to_string += " ";
				} else {
					list_to_string += ", ";
				}
				list_to_string += list_of_games[i];
			}
		}
		char buffer[LEN];
		memset(buffer, '\0', sizeof(buffer));
		strcpy(buffer, list_to_string.c_str());
		write(client_socket, buffer, LEN);
	}
};

#endif /* GAMESCOMMAND_H_ */
