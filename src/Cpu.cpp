/*
 * Cpu.cpp
 */
#include "Cpu.h"
#include <iostream>
using namespace std;

Cpu::Cpu(char player) {
	value_ = player;
	count_soldiers_ = 2;
	played_ = false;
}
Cpu::Cpu(char player, int soldiers) {
	value_ = player;
	count_soldiers_ = soldiers;
	played_= false;
}
bool Cpu::isPlayed() const {
	return played_;
}

void Cpu::setPlayed(bool status) {
	played_ = status;
}

void Cpu::makeMove(Player *opponent, Logic *logic) {
	cout << value_ <<": It's your move." << endl;
	logic->possibleMove(value_, opponent->getValue());
	//If there is not possible moves for the player.
	if (logic->isEmpty()) {
		return;
	}
	//cpu make best move for him
	Logic::Move best_move = logic->minMaxAlgorithm(opponent->getValue(),
			opponent->getSoldiers(), value_, count_soldiers_);
	cout << endl;
	logic->finishMove(best_move.row + 1, best_move.col + 1, value_); //finish the move of this player
	count_soldiers_ += logic->getDestroyed() + 1; //calculating count of this player
	opponent->setSoldiers(opponent->getSoldiers() - logic->getDestroyed()); //of other
	logic->clearDestroyed(); // reset destroyed variable to = 0
	played_ = true; //user played actual move
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
