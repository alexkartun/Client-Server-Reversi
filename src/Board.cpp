/*
 * Board.cpp
 *	Alex Kartun & Ofir Sharon
 *	324429216   & 204717664
 */
#include "Board.h"
#include <stdexcept>
using namespace std;

Board::Board(int size_board) {
	size_ = size_board;
	board_ = new char*[size_];
	for(int i = 0; i < size_; i++) {
	    board_[i] = new char[size_];
	    for (int j = 0; j < size_; j++) {
	    	//init all the cells of board to ' '
	        board_[i][j] = ' ';
	    }
	}
	board_[size_ / 2 - 1][size_ / 2 - 1] = 'O';
	board_[size_ / 2 - 1][size_ / 2] = 'X';
	board_[size_ / 2][size_ / 2 - 1] = 'X';
	board_[size_ / 2][size_ / 2] = 'O';
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
	if (row < 0 || col < 0) {
		throw invalid_argument("Negative index");
	}
	if (row >= size_ || col >= size_) {
		throw invalid_argument("Out of range");
	}
	board_[row][col] = player;
}

char Board::getValue(int row, int col) const {
	if (row < 0 || col < 0) {
		throw invalid_argument("Negative index");
	}
	if (row >= size_ || col >= size_) {
		throw invalid_argument("Out of range");
	}
	return board_[row][col];
}

void Board::resetAllValues() {
	for(int i = 0; i < size_; i++) {
		for (int j = 0; j < size_; j++) {
			//init all the cells of board to ' '
			board_[i][j] = ' ';
		}
	}
}
