/*
 * Console.cpp
 */
#include "Console.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

void Console::printBoard() const {
	//First row of the board
    cout << " ";
    for (int i = 1; i <= size_; i++) {
        cout << "| " << i << " ";
    }
    cout << "|" << endl;
    cout << string(size_ * 4 + 2, '-') << endl;
    //All other rows of the board
    for (int i = 0; i < size_; i++) {
        cout << i + 1;
        for (int j = 0; j < size_; j++) {
            cout << "| " << board_[i][j] << " ";
        }
        cout << "|" << endl;
        cout << string(size_ * 4 + 2, '-') << endl;
    }
}

string Console::toString() const {
	string to_string_repr = "";
	stringstream ss;
	to_string_repr += "Current Board: \n\n";
	for (int i = 1; i <= size_; i++) {
		to_string_repr += "| ";
		ss << i;
		to_string_repr += ss.str() + " ";
		ss.str("");
	}
	to_string_repr += "|\n";
	to_string_repr += string(size_ * 4 + 2, '-') + "\n";
	for (int i = 0; i < size_; i++) {
		ss << i + 1;
		to_string_repr += ss.str();
		ss.str("");
	    for (int j = 0; j < size_; j++) {
	    	to_string_repr += "| ";
	    	ss.str(string(1, board_[i][j]));
	    	to_string_repr += ss.str() + " ";
	    	ss.str("");
	    }
	    to_string_repr += "|\n";
	    to_string_repr += string(size_ * 4 + 2, '-') + "\n";
	}
	return to_string_repr;
}
