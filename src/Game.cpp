/*
 * Game.cpp
 */
#include <iostream>
#include "Game.h"
#include "User.h"
#include "Cpu.h"
#include "Logic.h"
using namespace std;

Game::Game() {
	current_ = new User('X');
	opponent_ = new Cpu('O'); //is computer
	running_ = false;
	passed_ = false;
	logic_game_ = NULL;
}

Game::~Game() {
	delete current_;
	delete opponent_;
	delete logic_game_;
}

void Game::initGame(int size) {
	if (size <= 0) {
		throw invalid_argument("Negative argument");
	}
	logic_game_ = new Logic(size);
}

void Game::startGame() {
	cout << "Current Board:" << endl;
	cout << endl;
	logic_game_->getBoard()->printBoard();
	running_ = true;
}

bool Game::getStatus() const {
	return running_;
}

void Game::endGame() {
	if (opponent_->getSoldiers() > current_->getSoldiers()) {
		cout << endl << "White player win with " << opponent_->getSoldiers() << " soldiers!" << endl;
	} else if (current_->getSoldiers() > opponent_->getSoldiers()){
		cout << endl << "Black player win with " << current_->getSoldiers() << " soldiers!" << endl;
	} else {
		cout << endl <<  "Draw!" << endl;
	}
}

void Game::passTurn() {
	if (passed_) { //if last turn was passed and this too, meaning not turns possible for both players
		cout << "No possible moves. Game is Over!" << endl;
		running_ = false; //if passed is true thats mean that both players dont have moves so the game is over.
		return;
	}
	cout << "No possible moves. Play passes back to other player." << endl;
	passed_ = true;
}

void Game::playTurn() {
	if (current_->isPlayed()) {
		opponent_->makeMove(current_, logic_game_); //opponent turn
		current_->setPlayed(false);
		if (!opponent_->isPlayed()) {
			opponent_->setPlayed(true);
			passTurn();
		} else {
			passed_ = false;
		}
	} else { /*same for current and opponent*/
		current_->makeMove(opponent_, logic_game_); //current turn
		opponent_->setPlayed(false); //after current turn, opponent status should be not played
		if (!current_->isPlayed()) { // if played so passed is should we false, otherwise it will be true
			current_->setPlayed(true); //and will go to passed function
			passTurn();
		} else {
			passed_ = false;
		}
	}
}
