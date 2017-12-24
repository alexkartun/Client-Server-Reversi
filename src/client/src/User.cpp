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
	// Convert chars to int.
	row = move[0] - 48;
	col = move[3] - 48;
	logic->possibleMove(value_, opponent->getValue());
	// Finish the move of this player and updating his soldiers and opponent's.
	int curr_sold = count_soldiers_;
	int opp_sold = opponent->getSoldiers();
	logic->finishMove(row, col, value_, &curr_sold, &opp_sold);
	count_soldiers_ = curr_sold;
	opponent->setSoldiers(opp_sold);
	cout << value_ << " played (" << row << "," << col << ")" << endl << endl;
}

void User::makeLocalMove(Player *opponent, Logic *logic, char *buffer) {
	makeMove(opponent, logic);
	if (!played_) {
		strcpy(buffer, "NoMove");
	} else {
		string str = logic->getSelectedMove();
		strcpy(buffer, str.c_str());
	}
}

void User::makeMove(Player *opponent, Logic *logic) {
	played_ = false;
	cout << value_ <<": It's your move." << endl;
	logic->possibleMove(value_, opponent->getValue());
	//If there is not possible moves for the player.
	if (logic->isEmpty()) {
		return;
	}
	logic->printMoves();
	cout << "Please enter your move row,col:";
	// Input validation.
	string input;
	int row, col;
	do {
		getline(cin, input);
		if (checkValidation(input)) {
			// Convert char do int.
			row = input.at(0) - 48;
			col = input.at(2) - 48;
			break;
		} else {
			cout << "Please enter your move row,col again:";
		}
	} while(true);
	cout << endl;
	// Finish the move of this player and updating his soldiers and opponent's.
	int curr_sold = count_soldiers_;
	int opp_sold = opponent->getSoldiers();
	logic->finishMove(row, col, value_, &curr_sold, &opp_sold);
	count_soldiers_ = curr_sold;
	opponent->setSoldiers(opp_sold);
	cout << value_ << " played (" << row << "," << col << ")" << endl << endl;
	played_ = true;
}

bool User::checkValidation(string input) {
	if (input.length() == 3) {
		if (isdigit(input.at(0)) && input.at(1) == ' ' && isdigit(input.at(2))){;
			return true;
		} else {
			return false;
		}
	}
	return false;
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
