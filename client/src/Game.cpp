/*
 * Game.cpp
 */
#include <iostream>
#include "Game.h"
#include "User.h"
#include "Cpu.h"
#include <stdexcept>
#include <string.h>
using namespace std;

Game::Game(int mod, int size) {
	user_ = new User('X');
	if (mod == 1) {
		opponent_ = new User('O');
	} else {
		opponent_ = new Cpu('O');
	}
	running_ = false;
	passed_ = false;
	initGame(size);
}

Game::Game(int size, char *player) {
	if (strcmp(player, "1") == 0) {
		user_ = new User('X');
		opponent_ = new User('O');
	} else {
		user_ = new User('O');
		opponent_ = new User('X');
	}
	running_ = false;
	passed_ = false;
	initGame(size);
}

Game::~Game() {
	delete user_;
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
	string opponent, user;
	if (opponent_->getValue() == 'X') {
		opponent = "Black";
	} else {
		opponent = "White";
	}
	if (user_->getValue() == 'X') {
		user = "Black";
	} else {
		user = "White";
	}
	if (opponent_->getSoldiers() > user_->getSoldiers()) {
		cout << endl << opponent << " player win with " << opponent_->getSoldiers() << " soldiers!" << endl;
	} else if (user_->getSoldiers() > opponent_->getSoldiers()){
		cout << endl << user << " player win with " << user_->getSoldiers() << " soldiers!" << endl;
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

void Game::playRemoteTurn(char *move) {
	if (strcmp(move, "NoMove") != 0) {
		opponent_->makeRemoteMove(user_, logic_game_, move);
		passed_ = false;
	} else {
		cout << "Opponent don't have move." << endl << endl;
		if (passed_) {
			cout << "No possible moves for both players. Game is Over!" << endl;
			running_ = false;
			return;
		}
		passed_ = true;
	}
}

void Game::playLocalTurn(char *move) {
	user_->makeLocalMove(opponent_, logic_game_, move);
	if (strcmp(move, "NoMove") == 0) {
		if (passed_) {
			cout << "No possible moves for both players. Game is Over!" << endl;
			running_ = false;
			return;
		}
		cout << "No possible moves. Play passes back to other player." << endl;
		passed_ = true;
	} else {
		passed_ = false;
	}
}

void Game::makeTurn() {
	if (user_->isPlayed()) {
		//opponent turn
		opponent_->makeMove(user_, logic_game_);
		user_->setPlayed(false);
		if (!opponent_->isPlayed()) {
			opponent_->setPlayed(true);
			passTurn();
		} else {
			passed_ = false;
		}
	/*same for current and opponent*/
	} else {
		//current turn
		user_->makeMove(opponent_, logic_game_);
		//after current turn, opponent status should be not playe
		opponent_->setPlayed(false);
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
