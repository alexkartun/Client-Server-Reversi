/*
 * User.cpp
 */
#include "User.h"
#include <iostream>
using namespace std;

User::User(char player) {
	value_ = player;
	count_soldiers_ = 2;
	played_ = false;
}

bool User::isPlayed() const {
	return played_;
}

void User::setPlayed(bool status) {
	played_ = status;
}

void User::makeMove(Player *opponent, Logic *logic_game) {
	cout << value_ <<": It's your move." << endl;
	logic_game->possibleMove(value_, opponent->getValue());
	//If there is not possible moves for the player.
	if (logic_game->isEmpty()) {
		return;
	}
	logic_game->printMoves();
	//Choosing the move that player want to make with validality checking
	cout << "Please enter your move row,col:";
	string input;
	int row, col;
	do { //loop that checking the validality of the move the user want to make, will run till entered valid move
		getline(cin, input);
		if (input.length() == 3 && isdigit(input.at(0)) && input.at(1) == ' ' && isdigit(input.at(2))) {
			row = input[0] - 48; //convert from ascii to int
			col = input[2] - 48;
			if (logic_game->checkValidality(Logic::Move(row, col))) {
				break;
			} else {
				cout << "Please enter your move row,col again:";
			}
		} else {
			cout << "Please enter your move row,col again:";
		}
	} while(true);
	cout << endl;
	logic_game->finishMove(row, col, value_); //finish the move of this player
	count_soldiers_ += logic_game->getDestroyed() + 1; //calculating count of this player
	opponent->setSoldiers(opponent->getSoldiers() - logic_game->getDestroyed()); //of other
	logic_game->clearDestroyed(); // reset destroyed variable to = 0
	played_ = true; //user played actual move
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
