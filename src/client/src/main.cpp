/*
 * main.cpp
 */
#include "Menu.h"

/**
 * Main Ex5.
 */
int main1() {
	Menu *menu = new Menu();
	if (menu->lobby() == failure) {
		delete menu;
		exit(failure);
	}
	delete menu;
	exit(success);
}


