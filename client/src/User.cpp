/*
 * User.cpp
 */
#include "User.h"
#include "Logic.h"
#include <iostream>
#include <string.h>
using namespace std;

User::User(char player) {
	value_ = player;
	count_soldiers_ = NUM_PLAYERS;
	played_ = false;
}

bool User::isPlayed() const {
	return played_;
}

void User::setPlayed(bool status) {
	played_ = status;
}

void User::makeRemoteMove(Player *opponent, Logic *logic, char *move) {
	int row, col;
	row = move[0] - 48;
	col = move[3] - 48;
	logic->possibleMove(value_, opponent->getValue());
	logic->finishMove(row, col, value_);
	count_soldiers_ += logic->getDestroyed() + 1;
	opponent->setSoldiers(opponent->getSoldiers() - logic->getDestroyed());
	logic->clearDestroyed();
	cout << value_ << " played (" << row << "," << col << ")" << endl;
	cout << endl;
	played_ = true;
}

void User::makeLocalMove(Player *opponent, Logic *logic, char *buffer) {
	Logic::Move m = makeMove(opponent, logic);
	if (m == Logic::Move(-1, -1)) {
		strcpy(buffer, "NoMove");
	} else {
		string str = m.toString();
		strcpy(buffer, str.c_str());
	}
}

Logic::Move User::makeMove(Player *opponent, Logic *logic) {
	cout << value_ <<": It's your move." << endl;
	logic->possibleMove(value_, opponent->getValue());
	//If there is not possible moves for the player.
	if (logic->isEmpty()) {
		return Logic::Move(-1, -1);
	}
	logic->printMoves();
	//Choosing the move that player want to make with validality checking
	cout << "Please enter your move row,col:";
	//loop that checking the validality of the move the user want to make,
	//will run till entered valid move
	string input;
	int row, col;
	do {
		getline(cin, input);
		if (logic->inputValdiation(input, &row, &col)) {
			break;
		} else {
			cout << "Please enter your move row,col again:";
		}
	} while(true);
	cout << endl;
	//finish the move of this player
	logic->finishMove(row, col, value_);
	cout << value_ << " played (" << row << "," << col << ")" << endl << endl;
	Logic::Move new_move(row, col);
	//calculating count user
	count_soldiers_ += logic->getDestroyed() + 1;
	//of other
	opponent->setSoldiers(opponent->getSoldiers() - logic->getDestroyed());
	// reset destroyed variable to = 0
	logic->clearDestroyed();
	//user played actual move
	played_ = true;
	return new_move;
}

unsigned int User::getSoldiers() const {
	return count_soldiers_;
}

void User::setSoldiers(int new_count) {
	count_soldiers_ = new_count;
}

char User::getValue() const {
	return value_;
}
