/*
 * User.h
 */
#ifndef USER_H_
#define USER_H_
#include "Player.h"
#include "Logic.h"

typedef enum command {play, close_game, notvalid} COMMAND;

class User: public Player {
public:
	User(char);
	void makeMove(Player *, Logic *);
	unsigned int getSoldiers() const;
	char getValue() const;
	void setSoldiers(int);
	bool isPlayed() const;
	void setPlayed(bool);
	/**
	 * Update remote player move.
	 */
	void updateRemoteMove(Player *, Logic *, char *);
	/**
	 * User choosing command for remote game.
	 */
	COMMAND chooseCommand(char *buffer, string gameName, Logic *logic);
	/**
	 * Checking if user's input is correct.
	 */
	COMMAND checkCommand(string input, string gameName, Logic *logic);
	/**
	 * Make local move in remote game.
	 */
	void makeLocalMove(Player *, Logic *, char *, string gameName);
	/**
	 * Check validation of user's input.
	 */
	bool checkNumericValidation(string input);
	/**
	 * Start the move.
	 */
	bool startMove(Player *opponent, Logic * logic);
	/**
	 * User choosing his move.
     */
	void chooseMove(int *row, int *col, Logic *logic);
	/**
	 * End the move.
	 */
	void finishMove(Player *opponent, Logic *logic, int row, int col);
private:
	char value_; // value of th player
	int count_soldiers_; //actual count of this player's soldiers on the field
	bool played_; //booleab if played = true or false if dont have any move to make
};

#endif /* USER_H_ */
