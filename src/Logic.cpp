/*
 * Logic.cpp
 */
#include "Logic.h"
#include "Console.h"
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

Logic::Move Logic::minMaxAlgorithm(char opponent, int opponent_soldiers, char current, int current_soldiers) {
	MoveArrayMap temp_map; //temp map of moves we will iterate over
	temp_map.insert(moves_.begin(), moves_.end());
	moves_.clear();
	map<Move,int> grade_per_move; //map of move and his grade
	Board *temp_board = new Console(gaming_board_->getSize()); //temp board that will sit on memory for backup
	temp_board->resetAllValues();
	for (unsigned int i = 0; i < soldiers_.size(); i++) { //init the temp board with all values of main board
		temp_board->setValue(soldiers_[i].row, soldiers_[i].col,
		gaming_board_->getValue(soldiers_[i].row, soldiers_[i].col));
	}
	vector<Move> temp_soldiers(soldiers_); //temp vector of soldiers that on the field before making the move.
	for (MoveArrayMap::const_iterator it = temp_map.begin(); it != temp_map.end(); it++) { //iterate over
		/**********************Make the move by changing the enemies********************/
		gaming_board_->setValue(it->first.row - 1, it->first.col - 1, current);
		set<Move> enemies = temp_map.find(it->first)->second;
		for (set<Move>::const_iterator it_s = enemies.begin(); it_s != enemies.end(); it_s++) {
			destroyed_enemies_++;
			gaming_board_->setValue(it_s->row - 1, it_s->col - 1, current);
		}
		int cpu_soldiers = current_soldiers + 1 + destroyed_enemies_; //new count of cpu soldiers
		int user_soldiers = opponent_soldiers - destroyed_enemies_; //new count of user soldiers
		soldiers_.push_back(Move(it->first.row - 1, it->first.col - 1)); //push the new move
		/*Now after cpu made a mov on the memory we want to check the possible moves of the user and his grading*/
		possibleMove(opponent, current);
		grade_per_move[Move(it->first.row - 1, it->first.col - 1)] = bestOpponentMove(cpu_soldiers, user_soldiers);
		/*After we foiund the best move that user can do we insert this grade to the map of grades*/
		/*And now we can clear the soldiers vector and moves map and board
		 * of the game to pre status of the board,cause we didnt actually made a move*/
		soldiers_.clear();
		moves_.clear();
		gaming_board_->resetAllValues();
		for (unsigned int i = 0; i < temp_soldiers.size(); i++) {
			gaming_board_->setValue(temp_soldiers[i].row, temp_soldiers[i].col,
			temp_board->getValue(temp_soldiers[i].row, temp_soldiers[i].col));
			soldiers_.push_back(Move(temp_soldiers[i].row, temp_soldiers[i].col));
		}
		destroyed_enemies_= 0;
	}
	moves_.insert(temp_map.begin(), temp_map.end()); //recover moves map
	delete temp_board; //destruc the board we used
	/*****From here on we will fnd the minimum grade and returns this move*****/
	int minimum = -1;
	map<Move, int>::const_iterator it;
	for (it = grade_per_move.begin(); it != grade_per_move.end(); it++) {
		if (it == grade_per_move.begin()) {
			minimum = grade_per_move.find(Move(it->first.row, it->first.col))->second;
		} else { //if minimun is bigger than next grade, so next grade will become minimum
			if (minimum > grade_per_move.find(Move(it->first.row, it->first.col))->second) {
				minimum = grade_per_move.find(Move(it->first.row, it->first.col))->second;
			}
		}
	}
	/*Iterate over the map, search for the minimum value we found and return the move*/
	for (it = grade_per_move.begin(); it != grade_per_move.end(); it++) {
		if (it->second == minimum) {
			break;
		}
	}
	return it->first;
}

int Logic::bestOpponentMove(int cpu_soldiers, int user_soldiers) {
	int grade_max = -1;
	int count_destroyed = 0;
	for (MoveArrayMap::const_iterator it = moves_.begin(); it != moves_.end(); it++) {
		set<Move> enemies = moves_.find(it->first)->second; //iterate over the posssible moves of the user
		for (set<Move>::const_iterator it_s = enemies.begin(); it_s != enemies.end(); it_s++) {
			count_destroyed++; //count the destroyed cpu enemies
		} /*check if this move is the best move that user can do.*/
		if (grade_max < (user_soldiers + count_destroyed + 1) - (cpu_soldiers - count_destroyed)) {
			grade_max = user_soldiers + count_destroyed + 1 - (cpu_soldiers - count_destroyed);
		}
		count_destroyed = 0;
	}
	return grade_max;
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
