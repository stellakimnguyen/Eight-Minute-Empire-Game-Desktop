#pragma once
#include <iostream>
#include "BiddingFacility.h"
#include "Map.h"
#include "Cards.h"
#include <list>
#include <vector>

// enum Colors { Red, Blue, Yellow, Green, White };

class Player
{
int goodsNumber[5] = { 0 }; //index correponds to: {forest, carrot, anvil, ore, crystal}

public:
	//int* numberOfCoin;//or token coins?
	int* playerNumber;
	int* playerAge;

	int* cubes;//armies
	int* discs;//cities
	int* tokenCoins;
	Colors chosenColor;

	std::list <Region>* regionOwned;
	std::list <Cards>* cards;

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
	void ignore();

	Player(int* numberOfPlayer, int playerNumber);
	Player(int playerNumber, int tc, int age, Colors c);
	~Player();

	void takeCard(Cards handCard);
	void displayCardsInHand();

	//GAME SCORE
	std::vector<int> nbArmiesAndCitiesPerRegion;
	void findNbArmiesPerRegion(int nbRegions);
	int score = 0;
	void categorizeGoods(string);
	int computeScore(vector<int> controllers, int);
	int* nbControllingRegions;
	int* totalNbArmies = 0;
};
