/*
 * Player.h
 */
#ifndef PLAYER_H_
#define PLAYER_H_
#define NUM_PLAYERS 2
#include "Logic.h"
/**
 * Interface player class.
 */
class Player {
public:
	/**
	 * Virtual deconstructor.
	 */
	virtual ~Player() { };
	/**
	 * The player or cpu will make the move.
	 * The algorithm of making moves located in logic for this our function getting as variable:
	 * Player * = the referense to opponent player.
	 */
	virtual void makeMove(Player *, Logic *) = 0;
	/**
	 * Returning the number of soldiers of specific player on the board.
	 */
	virtual unsigned int getSoldiers() const = 0;
	/**
	 * Return the value of the player.
	 */
	virtual char getValue() const = 0;
	/**
	 * Setting the new number of soldiers of the player.
	 */
	virtual void setSoldiers(int) = 0;
	/**
	 * Return true or false if the player played the round, meaning he did move.
	 */
	virtual bool isPlayed() const = 0;
	/**
	 * Seting the played boolean.
	 */
	virtual void setPlayed(bool) = 0;
};

#endif /* PLAYER_H_ */
