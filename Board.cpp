/*
 * Board.cpp
 *
 *  Created on: Nov 7, 2017
 *      Author: kartuna
 */
#include "Board.h"
Board::Board(int size_board) {
	size_ = size_board;
	board_ = new char*[size_];
	for(int i = 0; i < size_; i++) {
	    board_[i] = new char[size_];
	    for (int j = 0; j < size_; j++) {
	        board_[i][j] = ' '; //init all the cells of board to ' '
	    }
	}
	board_[3][3] = 'O';
	board_[3][4] = 'X';
	board_[4][3] = 'X';
	board_[4][4] = 'O';
}

Board::~Board() {
	for (int i = 0; i < size_; i++) {
		delete[] board_[i];
	}
	delete[] board_;
}
int Board::getSize() const {
	return size_;
}
void Board::setValue(int row, int col, char player) {
	board_[row][col] = player;
}
char Board::getValue(int row, int col) const {
	return board_[row][col];
}
