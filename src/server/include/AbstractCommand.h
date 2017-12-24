/*
 * AbstractCommand.h
 */
#ifndef ABSTRACTCOMMAND_H_
#define ABSTRACTCOMMAND_H_

#include "Command.h"
#include <iostream>

class AbstractCommand: public Command {
public:
	AbstractCommand(Server *server): ref_to_server(server) { }
protected:
	Server *ref_to_server;
};

#endif /* ABSTRACTCOMMAND_H_ */
