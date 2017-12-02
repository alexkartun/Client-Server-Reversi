/*
 * Console.h
 *	Alex Kartun & Ofir Sharon
 *	324429216   & 204717664
 */
#ifndef CONSOLE_H_
#define CONSOLE_H_
#include "Board.h"

class Console: public Board {

public:
	Console(int size): Board(size) { }
	void printBoard() const;
};

#endif /* CONSOLE_H_ */
