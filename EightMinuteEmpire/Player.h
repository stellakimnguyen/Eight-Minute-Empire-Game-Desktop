#pragma once
#include "Cards.h"
#include "BiddingFacility.h"
class Player
{


	int* cubes;
	int* disk;
	int* tokenArmies;
	Cards* cards;
	BiddingFacility* biddingFacility;
	int* regions[];
	int* addRegion();
	int* payCoin();
	int* placeNewArmies();
	int* moveArmies();
	int* moveOverLand();
	int* buildCity();
	int* destroyArmy();


};

