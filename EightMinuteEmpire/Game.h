#pragma once
#ifndef _GAME_H
#define _GAME_H


#include "MapLoader.h"
#include "Player.h"
#include "ObserverView.h"
#include <list>
#include <string>
#include <vector>

//enum Colors { Red, Blue, Yellow, Green, White };

class Game
{
	class ObserverView* view;

public:

	int* numberOfPlayers;
	int* numberOfRounds;
	std::list<Player>* players;
	Player* dummyPlayer;
	Player* chosenPlayerToDestroyArmy;
	bool dummyPlayerExists;
	Cards cardsDeck[42];
	Hand* hand;
	Map* map;
	int* startIndex;
	int* selectedCardIndex;

	//vector<int> playersScore; //score of each player
	//vector<int> playersCoins; //amount of coins each player owns
	//vector<int> playersArmies; //nb of armies each player owns
	//vector<int> nbRegionsOwn; //nb of regions each player owns

	std::vector<int> regionControllers;

	Game(int n, Map pMap);
	//Game(const Game &g);
	~Game();

	void addPlayer(Player* p);
	//void gameStart();
	void bidding();
	void startup(Region* startingRegion, Map gameMap);
	void gameLoop(Map gameMap);
	void convertPlayerAction(Cards card, Player player, Map gameMap);
	string return_value(int index);
	int findNumberOfRounds(int n);
	bool validateMoveArmies(Map m, Player p, int regionFromVal, int regionToVal, int value);
	bool validateMoveArmies2(Map m, Player p, int regionFromVal, int regionToVal, int value);
	void setView(ObserverView* v);
	//void compareScore(Map map);
	void compareScore2(Map currentMap);
		int nbRegions;
	void notify();

};

static int* supply;
static bool isTournament;

class EightMinEmpGame
{
};

//
#endif // !_GAME_H
