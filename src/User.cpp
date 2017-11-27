/*
 * User.cpp
 */
#include "User.h"
#include <iostream>
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

void User::makeMove(Player *cpu, Logic *logic) {
	cout << value_ <<": It's your move." << endl;
	logic->possibleMove(value_, cpu->getValue());
	//If there is not possible moves for the player.
	if (logic->isEmpty()) {
		return;
	}
	logic->printMoves();
	//Choosing the move that player want to make with validality checking
	cout << "Please enter your move row,col:";
	string input;
	int row, col;
	//loop that checking the validality of the move the user want to make,
	//will run till entered valid move
	do {
		getline(cin, input);
		if (input.length() == 3 && isdigit(input.at(0)) && input.at(1) == ' ' && isdigit(input.at(2))) {
			//convert from ascii to int
			row = input[0] - 48;
			col = input[2] - 48;
			if (logic->checkValidality(Logic::Move(row, col))) {
				break;
			} else {
				cout << "Please enter your move row,col again:";
			}
		} else {
			cout << "Please enter your move row,col again:";
		}
	} while(true);
	cout << endl;
	//finish the move of this player
	logic->finishMove(row, col, value_);
	//calculating count user
	count_soldiers_ += logic->getDestroyed() + 1;
	//of other
	cpu->setSoldiers(cpu->getSoldiers() - logic->getDestroyed());
	// reset destroyed variable to = 0
	logic->clearDestroyed();
	//user played actual move
	played_ = true;
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
