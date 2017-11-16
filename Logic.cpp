/*
 * Rules.cpp
 *
 *  Created on: Nov 7, 2017
 *      Author: kartuna
 */
#include "Logic.h"
#include <algorithm>
#include "Console.h"
#include <iostream>
#include <stdlib.h>
Logic::Logic(int size) {
	//initializing all the members of the class.
	gaming_board_ = new Console(size);
	soldiers_.push_back(Move(3, 3));
	soldiers_.push_back(Move(3, 4));
	soldiers_.push_back(Move(4, 3));
	soldiers_.push_back(Move(4, 4));
	destroyed_enemies_ = 0;
}
Logic::~Logic() {
	delete gaming_board_;
}
void Logic::possibleMove(char current, char opponent) {
	for (unsigned int i = 0; i < soldiers_.size(); i++) { //we want to run only on soldiers that on the field
		//and not all the board
		if (gaming_board_->getValue(soldiers_[i].row, soldiers_[i].col) == current) { //if this cell is current
			checkSurrounding(soldiers_[i].row, soldiers_[i].col, opponent); //calling the function to check the
			//surrounding of the i,j cell
		}
	}
}
void Logic::checkSurrounding(int i, int j, char opponent) {
	set<Move> temp_moves; // will save all posible enemies line
	int temp_row = i;
	//same checking for all the 8 checkings except of boundaries and direction of the check..
	if (i > 1) { //up
		while (temp_row - 1 > 0) { //iterativly go up
			if (gaming_board_->getValue(temp_row - 1, j) == opponent) {
				temp_moves.insert(Move(temp_row, j + 1));
				temp_row--;
			} else {
				break;
			}
		}
		if (temp_row != i && gaming_board_->getValue(temp_row - 1, j) == ' ') {
			if (moves_.find(Move(temp_row, j + 1)) != moves_.end()) { //if this move is already possible for other move
				moves_[Move(temp_row, j + 1)].insert(temp_moves.begin(), temp_moves.end()); //combine both enemies set
			} else {
				moves_[Move(temp_row, j + 1)] = temp_moves; //no such move yet so make it new
			}
		}
	}
	temp_moves.clear();
	int temp_col = j;
	if (j > 1) { //left
		while (temp_col - 1 > 0) { //iterativly go left
			if (gaming_board_->getValue(i, temp_col - 1) == opponent) {
				temp_moves.insert(Move(i + 1, temp_col));
				temp_col--;
			} else {
				break;
			}
		}
		if (temp_col != j && gaming_board_->getValue(i, temp_col - 1) == ' ') {
			if (moves_.find(Move(i + 1, temp_col)) != moves_.end()) {
				moves_[Move(i + 1, temp_col)].insert(temp_moves.begin(), temp_moves.end());
			} else {
				moves_[Move(i + 1, temp_col)] = temp_moves;
			}
		}
	}
	temp_moves.clear();
	temp_col = j;
	if (j < gaming_board_->getSize() - 2) { //right
		while (temp_col + 1 < gaming_board_->getSize() - 1) {
			if (gaming_board_->getValue(i, temp_col + 1) == opponent) {
				temp_moves.insert(Move(i + 1, temp_col + 2));
				temp_col++;
			} else {
				break;
			}
		}
		if (temp_col != j && gaming_board_->getValue(i, temp_col + 1) == ' ') {
			if (moves_.find(Move(i + 1, temp_col + 2)) != moves_.end()) {
				moves_[Move(i + 1, temp_col + 2)].insert(temp_moves.begin(), temp_moves.end());
			} else {
				moves_[Move(i + 1, temp_col + 2)] = temp_moves;
			}
		}
	}
	temp_moves.clear();
	temp_row = i;
	if (i < gaming_board_->getSize() - 2) { //down
		while (temp_row + 1 < gaming_board_->getSize() - 1) {
			if (gaming_board_->getValue(temp_row + 1, j) == opponent) {
				temp_moves.insert(Move(temp_row + 2, j + 1));
				temp_row++;
			} else {
				break;
			}
		}
		if (temp_row != i && gaming_board_->getValue(temp_row + 1, j) == ' ') {
			if (moves_.find(Move(temp_row + 2, j + 1)) != moves_.end()) {
				moves_[Move(temp_row + 2, j + 1)].insert(temp_moves.begin(), temp_moves.end());
			} else {
				moves_[Move(temp_row + 2, j + 1)] = temp_moves;
			}
		}
	}
	temp_moves.clear();
	temp_row = i;
	temp_col = j;
	if (i > 1 && j > 1) { //up - left
		while (temp_row - 1 > 0 && temp_col - 1 > 0) {
			if (gaming_board_->getValue(temp_row - 1, temp_col - 1) == opponent) {
				temp_moves.insert(Move(temp_row, temp_col));
				temp_row--;
				temp_col--;
			} else {
				break;
			}
		} //if i != temp_row same for j
		if (temp_row != i && gaming_board_->getValue(temp_row - 1, temp_col - 1) == ' ') {
			if (moves_.find(Move(temp_row, temp_col)) != moves_.end()) {
				moves_[Move(temp_row, temp_col)].insert(temp_moves.begin(), temp_moves.end());
			} else {
				moves_[Move(temp_row, temp_col)] = temp_moves;
			}
		}
	}
	temp_moves.clear();
	temp_row = i;
	temp_col = j;
	if (i < gaming_board_->getSize() - 2 && j < gaming_board_->getSize() - 2) { //right - down
		while (temp_row + 1 < gaming_board_->getSize() - 1 && temp_col + 1 < gaming_board_->getSize() - 1) {
			if (gaming_board_->getValue(temp_row + 1, temp_col + 1) == opponent) {
				temp_moves.insert(Move(temp_row + 2, temp_col + 2));
				temp_row++;
				temp_col++;
			} else {
				break;
			}
		} //same for j
		if (temp_row != i && gaming_board_->getValue(temp_row + 1, temp_col + 1) == ' ') {
			if (moves_.find(Move(temp_row + 2, temp_col + 2)) != moves_.end()) {
				moves_[Move(temp_row + 2, temp_col + 2)].insert(temp_moves.begin(), temp_moves.end());
			} else {
				moves_[Move(temp_row + 2, temp_col + 2)] = temp_moves;
			}
		}
	}
	temp_moves.clear();
	temp_row = i;
	temp_col = j;
	if (i < gaming_board_->getSize() - 2 && j > 1) { //left - down
		while (temp_row + 1 < gaming_board_->getSize() - 1 && temp_col - 1 > 0) {
			if (gaming_board_->getValue(temp_row + 1, temp_col - 1) == opponent) {
				temp_moves.insert(Move(temp_row + 2, temp_col));
				temp_row++;
				temp_col--;
			} else {
				break;
			}
		} //same for j
		if (temp_row != i && gaming_board_->getValue(temp_row + 1, temp_col - 1) == ' ') {
			if (moves_.find(Move(temp_row + 2, temp_col)) != moves_.end()) {
				moves_[Move(temp_row + 2, temp_col)].insert(temp_moves.begin(), temp_moves.end());
			} else {
				moves_[Move(temp_row + 2, temp_col)] = temp_moves;
			}
		}
	}
	temp_moves.clear();
	temp_row = i;
	temp_col = j;
	if (i > 1 && j < gaming_board_->getSize() - 2) { //right - up
		while (temp_row - 1 > 0 && temp_col + 1 < gaming_board_->getSize() - 1) {
			if (gaming_board_->getValue(temp_row - 1, temp_col + 1) == opponent) {
				temp_moves.insert(Move(temp_row, temp_col + 2));
				temp_row--;
				temp_col++;
			} else {
				break;
			}
		} //same for j
		if (temp_row != i && gaming_board_->getValue(temp_row - 1, temp_col + 1) == ' ') {
			if (moves_.find(Move(temp_row, temp_col + 2)) != moves_.end()) {
				moves_[Move(temp_row, temp_col + 2)].insert(temp_moves.begin(), temp_moves.end());
			} else {
				moves_[Move(temp_row, temp_col + 2)] = temp_moves;
			}
		}
	}
}
bool Logic::checkValidality(Move p) {
	for (unsigned int i = 0; i < moves_.size(); i++) {
		if (moves_.find(p) != moves_.end()) {
			return true;
		}
	}
	return false;
}
bool Logic::isEmpty() const {
	return moves_.empty();
}
void Logic::printMoves() const {
	//Printing the possible move.
	cout << "Your possible moves: "; //iterativly go over the keys of the map
	for (MoveArrayMap::const_iterator it = moves_.begin(); it != moves_.end(); it++) {
		if (it != moves_.begin()) { cout << ","; }
		cout << "(" << it->first.row << "," << it->first.col << ")";
	}
	cout << endl;
	cout << endl;
}
void Logic::finishMove(int row, int col, char current) {
	//Change the value in row, col and change the enemy value.
	gaming_board_->setValue(row - 1, col - 1, current);
	set<Move> enemies = moves_.find(Move(row, col))->second; //destroy all the enemies the we set up before in
	//the posibble moves. iterativly go over the enemies and destroy them
	for (set<Move>::const_iterator it = enemies.begin(); it != enemies.end(); it++) {
		destroyed_enemies_++;
		gaming_board_->setValue(it->row - 1, it->col - 1, current);
	}
	gaming_board_->printBoard(); //printing the move
	cout << current << " played (" << row << "," << col << ")" << endl;
	cout << endl;
	soldiers_.push_back(Move(row - 1, col - 1)); //inserting this move as soldier on the field
	//clear the moves.
	moves_.clear();
}
Board* Logic::getBoard() const {
	return gaming_board_;
}
unsigned int Logic::getDestroyed() {
	return destroyed_enemies_;
}
void Logic::clearDestroyed() {
	destroyed_enemies_ = 0;
}
