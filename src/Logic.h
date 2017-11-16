/*
 * Logic.h
 */
#ifndef LOGIC_H_
#define LOGIC_H_
#include <vector>
#include <set>
#include <map>
#include "Board.h"
using namespace std;
/**
 * Header of logic class.
 */
class Logic {
public:
	/**
	 * Inner struct move for simple saving data.
	 */
	struct Move {
	    int row, col;
		Move(int row, int col): row(row), col(col) { }
		bool operator < (const Move &p) const {
			if (row < p.row) { return true; }
			if (row == p.row) { if (col < p.col) { return true; } }
			return false;
		}
		bool operator == (const Move &p) const {
			return row == p.row && col == p.col;
		}
	};
	typedef map<Move, set<Move> > MoveArrayMap; // making other typedef of the map for easily using
	/**
	 *
	 * Constructor.
	 */
	Logic(int);
	/**
	 * Deconstructor.
	 */
	~Logic();
	/**
	 * Scanning all the possible moves that current player can do, this function using with check surrounding
     * method.
     */
	void possibleMove(char, char);
	/**
	 * Helpful function that check all the surrounding of the current player for making
	 * the possible moves. This function running iterativly for every opponent cell he find near the current
     * player and if found possible move insert the enemies to set which will add to the map.
	 * row - the row of current player
	 * col - the col of current player
     * Player - the opponent we loking for
	 */
	void checkSurrounding(int, int, char);
	/**
	 * Checking if the move that user want to make is validal. Compating to all the possible moves.
     * Move - the move that user want to make
	 */
	bool checkValidality(Move);
	/**
	 * Checking if moves vector is empty after checking.
	 */
	bool isEmpty() const;
	/**
	 * Printing all the possible moves that the algorithm find for us.
	 */
	void printMoves() const;
	/**
	 * Finishing move by making the destroy enemy algorithm, reseting the moves and adding the move we did
	 * to the array
	 */
	void finishMove(int, int, char);
	/**
	 * Returning the board.
	 */
	Board* getBoard() const;
	/**
	 * Returning the number of destroyed enemies after the algorithm for calulating the count of each player.
	 */
	unsigned int getDestroyed();
	/**
	 * Reseting the destroyed enemies variable to 0.
	 */
	void clearDestroyed();
private:
	MoveArrayMap moves_;
	vector<Move> soldiers_; //list of all the soldiers on the field
	unsigned int destroyed_enemies_;
	Board *gaming_board_; //gaming board
};

#endif /* LOGIC_H_ */
