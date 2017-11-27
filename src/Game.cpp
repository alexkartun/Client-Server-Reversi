/*
 * Game.cpp
 */
#include <iostream>
#include "Game.h"
#include "User.h"
#include "Cpu.h"
using namespace std;

Game::Game() {
	user_ = new User('X');
	cpu_ = new Cpu('O');
	running_ = false;
	passed_ = false;
	logic_game_ = NULL;
}

Game::~Game() {
	delete user_;
	delete cpu_;
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
	if (cpu_->getSoldiers() > user_->getSoldiers()) {
		cout << endl << "White player win with " << cpu_->getSoldiers() << " soldiers!" << endl;
	} else if (user_->getSoldiers() > cpu_->getSoldiers()){
		cout << endl << "Black player win with " << user_->getSoldiers() << " soldiers!" << endl;
	} else {
		cout << endl <<  "Draw!" << endl;
	}
}

void Game::passTurn() {
	//if last turn was passed and this too, meaning not turns possible for both players
	if (passed_) {
		cout << "No possible moves. Game is Over!" << endl;
		//if passed is true thats mean that both players dont have moves so the game is over.
		running_ = false;
		return;
	}
	cout << "No possible moves. Play passes back to other player." << endl;
	passed_ = true;
}

void Game::playTurn() {
	if (user_->isPlayed()) {
		//opponent turn
		cpu_->makeMove(user_, logic_game_);
		user_->setPlayed(false);
		if (!cpu_->isPlayed()) {
			cpu_->setPlayed(true);
			passTurn();
		} else {
			passed_ = false;
		}
	/*same for current and opponent*/
	} else {
		//current turn
		user_->makeMove(cpu_, logic_game_);
		//after current turn, opponent status should be not playe
		cpu_->setPlayed(false);
		//if played so passed is should we false, otherwise it will be true
		if (!user_->isPlayed()) {
			//and will go to passed function
			user_->setPlayed(true);
			passTurn();
		} else {
			passed_ = false;
		}
	}
}
