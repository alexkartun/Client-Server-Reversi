/*
 * AbstractCommand.h
 */
#ifndef ABSTRACTCOMMAND_H_
#define ABSTRACTCOMMAND_H_

#include "Command.h"
#include <iostream>

/**
 * Abstract command class.
 */
class AbstractCommand: public Command {
public:
	AbstractCommand(Server *server): ref_to_server(server) { }
protected:
	Server *ref_to_server;   // saving reference to server for all his sons.
};

#endif /* ABSTRACTCOMMAND_H_ */
