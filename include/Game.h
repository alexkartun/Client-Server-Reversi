/*
 * Game.h
 */
#ifndef GAME_H_
#define GAME_H_
#include "Logic.h"
#include "Player.h"
/**
 * Header of class game that running the thread of the game.
 */
class Game {
public:
	/**
	 * Constructor.
	 */
	Game(string);
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
	//logic of the game will depends on the user choose
	Logic *logic_game_;
	//curent player
	Player *user_;
	//opponent player
	Player *opponent_;
	//if player dont have possible move this bollean become true.
	bool passed_;
	//the running bolean if the game, if this boolean become false game is over
	bool running_;
};

#endif /* GAME_H_ */
