/*
 * LobbyTest.cpp
 */

#include "Lobby.h"
#include "gtest/gtest.h"

TEST(LobbyTest, AddNewGame) {
	Lobby lobby;
	lobby.addNewGame("game", 1);
	EXPECT_EQ(lobby.addNewGame("game" , 1), false);
	EXPECT_EQ(lobby.addNewGame("Yrs" , 1), true);
}

TEST(LobbyTest, JoinGame) {
	Lobby lobby;
	lobby.addNewGame("game", 1);
	EXPECT_EQ(lobby.joinGame("game", 1), true);
	EXPECT_EQ(lobby.joinGame("Yrs" , 1), false);
	lobby.addNewGame("Yrs", 1);
	EXPECT_EQ(lobby.joinGame("Yrs" , 1), true);
}

TEST(LobbyTest, GetGames) {
	Lobby lobby;
	lobby.addNewGame("game", 1);
	vector<string> gamesOnHold;
	gamesOnHold.push_back("game");
	EXPECT_EQ(lobby.getGamesOnHold(), gamesOnHold);
	lobby.joinGame("game", 1);
	gamesOnHold.clear();
	EXPECT_EQ(lobby.getGamesOnHold(), gamesOnHold);
}
