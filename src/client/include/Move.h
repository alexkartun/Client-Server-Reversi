/*
 * Move.h
 */

#ifndef MOVE_H_
#define MOVE_H_
#include <string>
#include <sstream>
using namespace std;

class Move {
public:
	Move(int row, int col);
	/**
	 * Operator <
	 */
	bool operator < (const Move &p) const {
		if (row < p.row) { return true; }
		if (row == p.row) { if (col < p.col) { return true; } }
		return false;
	}
	/**
	 * Operator ==
	 */
	bool operator == (const Move &p) const {
		return row == p.row && col == p.col;
	}
	/**
	 * String representation of move. 'X, Y'
	 */
	string toString() const;
	int row;
	int col;
};

#endif /* MOVE_H_ */
