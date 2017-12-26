/*
 * GamesCommand.h
 */

#ifndef GAMESCOMMAND_H_
#define GAMESCOMMAND_H_

#include "AbstractCommand.h"

class GamesCommand: public AbstractCommand {
public:
	GamesCommand(Server *server): AbstractCommand(server) { }
	virtual void execute(string args, int client_socket) {
		vector<string> list_of_games = ref_to_server->getGamesOnHold();
		string list_to_string = "Active games on hold:";
		if (list_of_games.empty()) {
			list_to_string += " None!";
		} else {
			for (unsigned int i = 0; i < list_of_games.size(); i++) {
				if (i == 0) {
					list_to_string += " ";
				} else {
					list_to_string += ", ";
				}
				list_to_string += list_of_games[i];
			}
		}
		ref_to_server->writeToClient(client_socket, list_to_string.c_str());
	}
};

#endif /* GAMESCOMMAND_H_ */
