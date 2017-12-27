/*
 * Move.cpp
 */

#include "Move.h"

Move::Move(int row, int col): row(row), col(col) { }

string Move::toString() const {
	// Parsing move to string by stringstream.
	string to_string = "";
	stringstream ss;
	ss << row;
	to_string += ss.str() + " ";
	ss.str("");
	ss << col;
	to_string += ss.str();
	return to_string;
}
