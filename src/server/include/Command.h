/*
 * Command.h
 */
#include <vector>
#include <string>

using namespace std;

#ifndef COMMAND_H_
#define COMMAND_H_

class Command {
public:
	virtual void execute(string args, int client_socket) = 0;
	virtual ~Command() { }
};

#endif /* COMMAND_H_ */
