/*
 * Console.h
 */
#ifndef CONSOLE_H_
#define CONSOLE_H_
#include "Board.h"

class Console: public Board {

public:
	Console(int size): Board(size) { }
	void printBoard() const;
	string toString() const;
};

#endif /* CONSOLE_H_ */
