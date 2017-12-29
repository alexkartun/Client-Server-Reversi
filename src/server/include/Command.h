/*
 * Command.h
 */
#ifndef COMMAND_H_
#define COMMAND_H_
#include <vector>
#include <string>

using namespace std;
/**
 * Interface.
 */
class Command {
public:
	/**
	 * Execute the comand.
	 */
	virtual void execute(string args, int client_socket) = 0;
	virtual ~Command() { }
};

#endif /* COMMAND_H_ */
