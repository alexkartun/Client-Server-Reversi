/*
 * User.h
 *
 *  Created on: Nov 7, 2017
 *      Author: kartuna
 */
#ifndef USER_H_
#define USER_H_
#include "Player.h"
class User: public Player {
public:
	User(char);
	void makeMove(Player *, Logic *);
	unsigned int getSoldiers() const;
	char getValue() const;
	void setSoldiers(int);
	bool isPlayed() const;
	void setPlayed(bool);
private:
	char value_; // value of th player
	int count_soldiers_; //actual count of this player's soldiers on the field
	bool played_; //booleab if played = true or false if dont have any move to make
};
#endif /* USER_H_ */
