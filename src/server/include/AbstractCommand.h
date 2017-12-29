/*
 * AbstractCommand.h
 */
#ifndef ABSTRACTCOMMAND_H_
#define ABSTRACTCOMMAND_H_

#include "Command.h"
#include "Lobby.h"
#include <unistd.h>    // write and read to sockets.
#include <string.h>    // for strcpy.
#define LEN 256

/**
 * Abstract command class.
 */
class AbstractCommand: public Command {
public:
	AbstractCommand(Lobby *lobby): lobby(lobby) { }
protected:
	Lobby *lobby;   // saving reference to GameManager.
};

#endif /* ABSTRACTCOMMAND_H_ */
