#pragma once
#include "Cards.h"
#include "BiddingFacility.h"
#include "Map.h"
#include <list>

// enum Colors { Red, Blue, Yellow, Green, White };

class Player
{
public:
	//int* numberOfCoin;//or token coins?
	int* playerNumber;
	int* playerAge;


	int* cubes;//armies
	int* discs;//cities
	int* tokenCoins;

	Colors chosenColor;

	std::list <Region>* regionOwned;
	Cards* cards;

	BiddingFacility* biddingFacility;
	//int* regions[];//not needed?
	void addRegion(Region* regionToAdd);
	void payCoin(int* value);
	void placeNewArmies(Region* region, int* value);
	void moveArmies(Region* regionFrom, Region* regionTo, int* value);
	void moveOverLand(Region* regionFrom, Region* regionTo, int* value);
	void buildCity(Region* region);
	void destroyArmy(Region* region, int* value);
	void setChosenColor(Colors value);
	Player(int* numberOfPlayer, int playerNumber);
	Player(int playerNumber, int tc, int age, Colors c);
	~Player();
};

