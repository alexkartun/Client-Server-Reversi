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

void User::updateRemoteMove(Player *opponent, Logic *logic, char *move) {
	int row, col;
	// Convert chars to int.
	row = move[0] - 48;
	col = move[2] - 48;
	logic->possibleMove(value_, opponent->getValue());
	// Finish the move of this player and updating his soldiers and opponent's.
	int curr_sold = count_soldiers_;
	int opp_sold = opponent->getSoldiers();
	logic->finishMove(row, col, value_, &curr_sold, &opp_sold);
	count_soldiers_ = curr_sold;
	opponent->setSoldiers(opp_sold);
	cout << value_ << " played (" << row << "," << col << ")" << endl << endl;
}

void User::makeLocalMove(Player *opponent, Logic *logic, char *buffer, string gameName) {
	string str;
	// Checking if user can make local move.
	if (!startMove(opponent, logic)) {
		// If no and board is full return "end".
		if (logic->isFinished() == true) {
			str = "end";
			strcpy(buffer, str.c_str());
		// Otherwise return "NoMove".
		} else {
			str = "NoMove";
			strcpy(buffer, str.c_str());
		}
	} else {
	// User can make local move.
		// User choosing the comand he want to execute. If play do, otherwise user want to close the game.
		if (chooseCommand(buffer, gameName, logic) == play) {
			int row = buffer[0] - 48;    //Convert char do int.
			int col = buffer[2] - 48;
			finishMove(opponent, logic, row, col);
			str = "play ";
			str += logic->getSelectedMove();
			strcpy(buffer, str.c_str());
		} // otherwise buffer is close gameName
	}
}

COMMAND User::chooseCommand(char *buffer, string gameName, Logic *logic) {
	cout << "You can play 'X Y' or close 'name_game': ";
	string input;
	do {
		getline(cin, input);
			// Check the validality of both commands, if not valid input again.
			if (checkCommand(input, gameName, logic) != notvalid) {
				strcpy(buffer, input.c_str());
				return checkCommand(input, gameName, logic);
			} else {
				cout << "Please enter command again: " << endl;
			}
	} while(true);
}

COMMAND User::checkCommand(string input, string gameName, Logic *logic) {
	// If the input is Numeric
	if(checkNumericValidation(input)) {
		// Convert to int row and col.
		int row = input.at(0) - 48;
		int col = input.at(2) - 48;
		// Check if row and col is possible move user can do. If yes return otherwise check other command.
		if (logic->isPossibleMoveValidality(Move(row, col))) { 	return play; }
	}
	string::size_type pos = input.find(' ', 0);
	// If input is only one word, return not valid.
	if (pos == string::npos) {
		return notvalid;
	} else {
		// Check if first word is close and second word matching to the gameName.
		if (input.substr(0, pos).compare("close") == 0 && input.substr(pos + 1).compare(gameName) == 0) {
			return close_game;
		}
	}
	return notvalid;
}

void User::chooseMove(int *row, int *col, Logic *logic) {
	cout << "Please enter your move row,col:";
	// Input validation.
	string input;
	do {
		getline(cin, input);
		// Check numericValidation.
		if (checkNumericValidation(input)) {
			*row = input.at(0) - 48;    //Convert char do int.
			*col = input.at(2) - 48;
			// Check if this row and col, are possible move that user can make.
			if (logic->isPossibleMoveValidality(Move(*row, *col))) { break; }
		}
		cout << "Please enter your move row,col again:";
	} while(true);
	cout << endl;
}

void User::makeMove(Player *opponent, Logic *logic) {
	// Check if user can start move. If true continue if false return.
	if (!startMove(opponent, logic)) {
		return;
	}
	int row, col;
	// Choose row and col with validations.
	chooseMove(&row, &col, logic);
	//Finish move of user with chosen move, by updating the board, and soldiers.
	finishMove(opponent, logic, row, col);

}

bool User::startMove(Player *opponent, Logic * logic) {
	played_ = false;
	cout << value_ <<": It's your move." << endl;
	logic->possibleMove(value_, opponent->getValue());
	//If there is not possible moves for the player.
	if (logic->isEmpty()) {
		return false;
	}
	logic->printMoves();
	return true;
}


void User::finishMove(Player *opponent, Logic *logic, int row, int col) {
	// Finish the move of this player and updating his soldiers and opponent's.
	int curr_sold = count_soldiers_;
	int opp_sold = opponent->getSoldiers();
	logic->finishMove(row, col, value_, &curr_sold, &opp_sold);
	count_soldiers_ = curr_sold;
	opponent->setSoldiers(opp_sold);
	cout << value_ << " played (" << row << "," << col << ")" << endl << endl;
	played_ = true;
}

bool User::checkNumericValidation(string input) {
	if (input.length() == 3) {
		// Check if unput is 'X Y'.
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
