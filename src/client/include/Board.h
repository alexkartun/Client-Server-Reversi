/*
 * Board.h
 */
#ifndef BOARD_H_
#define BOARD_H_
#include <string>
using namespace std;
/**
 * Header of board Abstract class.
 */
class Board {
public:
	/**
	 * Constructor.
	 */
	Board(int);
	/**
	 * Virtual destractor.
	 */
	virtual ~Board();
	/**
	 * Abstract print board function will depends on board.
	 */
	virtual void printBoard() const = 0;
    /**
     * Get the size of board.
     */
    int getSize() const;
    /**
     * Get the value of cell in specific i, j.
     * int - row of the matrix
     * int - col of the matrix
     */
    char getValue(int, int) const;
    /**
     * Set value of cell in specific i, j.
     * int - row of the matrix
     * int - col of the matrix
     * char - the value of the player that played 'X' or 'O'
     */
    void setValue(int, int , char);
    /**
     * Reset all values of the board to ' '.
     */
    void resetAllValues();
protected:
    //actual size of the game
    int size_;
    //the n*n dynamic board of chars will represent the board of the game.
    char **board_;
};

#endif /* BOARD_H_ */
