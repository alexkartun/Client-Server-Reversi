/*
 * Game.h
 */
#ifndef GAME_H_
#define GAME_H_
#include "Client.h"
#include "Logic.h"
#include "Player.h"
/**
 * Header of class game that running the thread of the game.
 */
class Game {
public:
	/**
	 * Constructor for remote game.
	 */
	Game(int size, char player, string game);
	/**
	 * Constructor for local game
	 */
	Game(int, int);
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
	 * Play remote turn.
	 */
	void playRemoteTurn(char *move);
	/**
	 * Play local move.
	 */
	void playLocalTurn(char *move);
	/**
	 * Make move depends on the current player. Local playing.
	 * If got no move passing to opponent, if opponent as well dont have move the game is over.
	 */
	void makeTurn();
	/**
	 * Returning the actual state of the game, {true or false}.
	 */
	bool getStatus() const;
	/**
	 * Passing turn if the player dont have possible moves.
	 */
	void passTurn();
private:
	string gameName;
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
