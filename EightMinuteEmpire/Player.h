#ifndef _PLAYER_H
#define _PLAYER_H



#pragma once
#include <iostream>
#include "PlayerStrategies.h"
#include "BiddingFacility.h"
#include "Map.h"
//#include "Cards.h"
#include <list>
#include <vector>

// enum Colors { Red, Blue, Yellow, Green, White };

class Player
{
	PlayerStrategies* playerStrategy;
	int goodsNumber[5] = { 0 }; //index correponds to: {forest, carrot, anvil, ore, crystal}

public:
	//int* numberOfCoin;//or token coins?
	int* playerNumber;
	int* playerAge;

	int* cubes;//armies
	int* discs;//cities
	int* tokenCoins; // 	int playersCoins; //amount of coins each player owns


	Colors chosenColor;

	std::list <Region>* regionOwned;
	std::list <Cards>* cards;
	std::list <class MoveDesc>* moveDesc;

	int* playerScore; //score of player
	int playersArmies; //nb of armies each player owns
	int nbRegionsOwn; //nb of regions each player owns


	BiddingFacility* biddingFacility;
	//int* regions[];//not needed?
	void addRegion(Region* regionToAdd);
	void payCoin(int* value);
	void placeNewArmies(Region* region, int* value);
	void displayArmies();
	void moveArmies(Region* regionFrom, Region* regionTo, int* value);
	void moveOverLand(Region* regionFrom, Region* regionTo, int* value);
	void buildCity(Region* region);
	bool isRegionOwned(Region* region);
	void destroyArmy(Region* region, int* value);
	void setChosenColor(Colors value);
	void ignore();
	int choose_Card();
	int choose_target_region(string action, Map m, int);
	int choose_to_ignore_action(string action);
	int choose_destination_Region(string action, Map m, int fromRegion);
	int choose_number_army_move(int);
	int choose_playerID(int numberOfPlayers);
	Player();
	Player(int* numberOfPlayer, int playerNumber);
	Player(int playerNumber, int tc, int age, Colors c);
	Player(int pn, int tc, int age, Colors c, PlayerStrategies* pStrategy);
	~Player();

	void takeCard(Cards handCard);
	void displayCardsInHand();

	//GAME SCORE
	std::vector<int> nbArmiesAndCitiesPerRegion;
	void findNbArmiesPerRegion(int nbRegions);
	int score = 0;
	void categorizeGoods(string);
	//int computeScore(vector<int> controllers, int);

	void computeScore(Map map, bool);
	
	int* nbControllingRegions;
	int* totalNbArmies;
};

class MoveDesc {
public:
	Region* regionFrom;
	Region* regionTo;
};

/*
class Child : public Parent
{
public:
	int id_c;
};*/

#endif // !_PLAYER_H