/*
 * Cpu.h
 */
#ifndef CPU_H_
#define CPU_H_
#include "Player.h"
#include "Logic.h"
/**
 * Cpu derived player class.
 */
class Cpu: public Player {
public:
	Cpu(char);
	Cpu(char, int);
	void makeMove(Player *, Logic *);
	unsigned int getSoldiers() const;
	char getValue() const;
	void setSoldiers(int);
	bool isPlayed() const;
	void setPlayed(bool);
private:
	char value_; // value of the player
	int count_soldiers_; //actual count of this player's soldiers on the field
	bool played_; //booleab if played = true or false if dont have any move to make
};

#endif /* CPU_H_ */
