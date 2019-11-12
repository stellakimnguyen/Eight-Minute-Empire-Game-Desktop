#pragma once

#include "MapLoader.h"
#include <list>
#include <string>

//enum Colors { Red, Blue, Yellow, Green, White };

class Game
{

public:

	int* numberOfPlayers;
	std::list<Player>* players;
	Player* dummyPlayer;
	bool dummyPlayerExists;
	Cards cardsDeck[42];
	Hand* hand;
	Map* map;
	int* startIndex;

	Game(int n, Map pMap);
	//Game(const Game &g);
	~Game();

	void addPlayer(Player p);
	void bidding();
	void startup(Region startingRegion);
	void gameLoop();
	string return_value(int index);
};

class EightMinEmpGame
{
};

