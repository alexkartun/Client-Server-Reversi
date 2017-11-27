/*
 * Console.h
 *
 *  Created on: Nov 7, 2017
 *      Author: kartuna
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
