/*
 * Cpu.cpp
 */
#include "Cpu.h"
#include <iostream>
using namespace std;

Cpu::Cpu(char player) {
	value_ = player;
	count_soldiers_ = NUM_PLAYERS;
	played_ = false;
}

bool Cpu::isPlayed() const {
	return played_;
}

void Cpu::setPlayed(bool status) {
	played_ = status;
}

void Cpu::makeMove(Player *opponent, Logic *logic) {
	logic->possibleMove(value_, opponent->getValue());
	//if there is not possible moves for the player just return
	if (logic->isEmpty()) {
		return;
	}
	//cpu make best move for him via min-max algorithm
	Move best_move = logic->minMaxAlgorithm(opponent->getValue(),
			opponent->getSoldiers(), value_, count_soldiers_);
	cout << endl;
	// Updating cpu's move on board and update soldiers of both cpu and user.
	int curr_sold = count_soldiers_;
	int opp_sold = opponent->getSoldiers();
	logic->finishMove(best_move.row + 1, best_move.col + 1, value_, &curr_sold, &opp_sold);
	count_soldiers_ = curr_sold;
	opponent->setSoldiers(opp_sold);
	cout << value_ << " played (" << best_move.row + 1 << ","
			<< best_move.col + 1 << ")" << endl << endl;
	played_ = true;
}

unsigned int Cpu::getSoldiers() const {
	return count_soldiers_;
}

void Cpu::setSoldiers(int new_count) {
	count_soldiers_ = new_count;
}

char Cpu::getValue() const {
	return value_;
}
