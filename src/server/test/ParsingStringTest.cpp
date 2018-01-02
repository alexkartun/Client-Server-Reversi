/*
 * ParsingStringTest.cpp
 */
#include "gtest/gtest.h"

using namespace std;

vector<string> Parsing(char* buffer) {
	vector<string> argumentsVector;
	string str(buffer);
	string::size_type pos = str.find(' ', 0);
	if (pos != std::string::npos) {
		argumentsVector.push_back(str.substr(0, pos));
		argumentsVector.push_back(str.substr(pos + 1));
	} else {
		argumentsVector.push_back(str);
		argumentsVector.push_back("");
	}
	return argumentsVector;
}

TEST(ParsingTest, HandleParsing) {
	char buffer[255];
	strcpy(buffer, "start game");
	vector<string> vector;
	vector.push_back("start");
	vector.push_back("game");
	EXPECT_EQ(Parsing(buffer), vector);
	vector.clear();
	strcpy(buffer, "join game");
	vector.push_back("join");
	vector.push_back("game");
	EXPECT_EQ(Parsing(buffer), vector);
	vector.clear();
	strcpy(buffer, "list_games");
	vector.push_back("list_games");
	vector.push_back("");
	EXPECT_EQ(Parsing(buffer), vector);
}

