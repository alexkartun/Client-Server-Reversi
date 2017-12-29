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

Game::Game(int size, char player, string game) {
	if (player == 'X') {
		user_ = new User('X');
		opponent_ = new User('O');
	} else {
		user_ = new User('O');
		opponent_ = new User('X');
	}
	gameName = game;
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
	cout << endl;
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
	cout << "No possible moves for both players. Game is Over!" << endl << endl;
	if (opponent_->getSoldiers() > user_->getSoldiers()) {
		cout << endl << opponent << " player win with " << opponent_->getSoldiers()
				<< " soldiers!" << endl;
	} else if (user_->getSoldiers() > opponent_->getSoldiers()){
		cout << endl << user << " player win with " << user_->getSoldiers()
				<< " soldiers!" << endl;
	} else {
		cout << endl <<  "Draw!" << endl;
	}
}

void Game::passTurn() {
	//if last turn was passed and this too, meaning not turns possible for both players
	if (passed_) {
		//if passed is true thats mean that both players dont have moves so the game is over.
		running_ = false;
		return;
	}
	cout << "No possible moves. Play passes back to other player." << endl;
	passed_ = true;
}

void Game::updateRemoteTurn(char *move) {
	// If remote player had no moev print suitable message otherwise update user board by reot's move.
	if (strcmp(move, "NoMove") != 0) {
		opponent_->updateRemoteMove(user_, logic_game_, move);
		passed_ = false;
	} else {
		// If the game already passed so game is over.
		if (passed_ == true) { running_ = false; return;}
		passed_ = true;
		cout << "Opponent don't have move." << endl;
	}
}

void Game::playLocalTurn(char *move) {
	// Make local move of current user.
	user_->makeLocalMove(opponent_, logic_game_, move, gameName);
	// If user dont have moves.
	if (strcmp(move, "NoMove") == 0) {
		// And if the game passe already, finish game. If no print suitable message.
		if (passed_ == true) { running_ = false; return;}
		passed_ = true;
		cout << "No possible moves. Play passes back to other player." << endl;
	} else {
		// User made move or want to close the game.
		passed_ = false;
		string command("close ");
		command += gameName;
		// If user want to close  the game or, board is full, finish the game.
		if (strcmp(move, command.c_str()) == 0 || strcmp(move, "end") == 0 || logic_game_->isFinished()){
			running_ = false;
		}
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
