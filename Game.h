/*
 * Game.h
 *
 *  Created on: Oct 27, 2017
 *      Author: kartuna
 */
#ifndef GAME_H_
#define GAME_H_
#include "Player.h"
#include "Logic.h"
/**
 * Header of class game that running the thread of the game.
 */
class Game {
public:
	/**
	 * Destructor.
	 */
	~Game();
	/**
	 * Init the data of the game.
	 */
	void initGame(int);
	/**
	 * Start the running of the game.
	 */
	void startGame();
	/**
     * End of game. Represent the winner.
	 */
	void endGame();
	/**
	 * Make move depends on the current player.
	 * If got no move passing to opponent, if opponent as well dont have move the game is over.
	 */
	void playTurn();
	/**
	 * Returning the actual state of the game, {true or false}.
	 */
	bool getStatus() const;
	/**
	 * Passing turn if the player dont have possible moves.
	 */
	void passTurn();
private:
	Logic *logic_game_; //logic of the game will depends on the user choose
	Player *current_; //cuurent player
	Player *opponent_; //opponent player
	bool passed_; //if player dont have possible move this bollean become true.
	bool running_; //the running bolean if the game, if this boolean become false game is over
};
#endif /* GAME_H_ */
