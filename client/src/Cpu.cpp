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

Logic::Move Cpu::makeMove(Player *opponent, Logic *logic) {
	logic->possibleMove(value_, opponent->getValue());
	//if there is not possible moves for the player just return
	if (logic->isEmpty()) {
		return Logic::Move(-1, -1);
	}
	//cpu make best move for him via min-max algorithm
	Logic::Move best_move = logic->minMaxAlgorithm(opponent->getValue(),
			opponent->getSoldiers(), value_, count_soldiers_);
	cout << endl;
	//finish the move of this player
	logic->finishMove(best_move.row + 1, best_move.col + 1, value_);
	cout << value_ << " played (" << best_move.row + 1 << "," << best_move.col + 1 << ")" << endl << endl;
	//calculating count of cpu
	count_soldiers_ += logic->getDestroyed() + 1;
	opponent->setSoldiers(opponent->getSoldiers() - logic->getDestroyed());
	//reset destroyed variable to  0
	logic->clearDestroyed();
	//cpu did move
	played_ = true;
	return best_move;
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
