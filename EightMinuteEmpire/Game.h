#pragma once

#include "MapLoader.h"
#include <list>
#include <string>
#include <vector>

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
	int* selectedCardIndex;

	vector<int> playersScore; //score of each player
	vector<int> playersCoins; //amount of coins each player owns
	vector<int> playersArmies; //nb of armies each player owns
	vector<int> nbRegionsOwn; //nb of regions each player owns

	Game(int n, Map pMap);
	//Game(const Game &g);
	~Game();

	void addPlayer(Player p);
	void bidding();
	void startup(Region startingRegion);
	void gameLoop(Map gameMap);

	void convertPlayerAction(Cards card, Player player, Map gameMap);
	bool validateMoveArmies(Map m, Player p, int regionFromVal, int regionToVal, int value);

	string return_value(int index);

	void compareScore(Map map);
	int nbRegions;

};

class EightMinEmpGame
{
};

std::vector<int> regionControllers;
