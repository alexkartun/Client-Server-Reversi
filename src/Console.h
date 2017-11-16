/*
 * Console.h
 */
#ifndef CONSOLE_H_
#define CONSOLE_H_
#include "Board.h"
/**
 * Header of class Console that derives from Board.
 */
class Console: public Board {
public:
	Console(int size): Board(size) { }
	void printBoard() const;
};

#endif /* CONSOLE_H_ */
