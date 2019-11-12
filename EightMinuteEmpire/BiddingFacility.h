#pragma once
#include <string>
#include <vector>

using namespace std;

struct BiddingFacility
{
	//std::string* color; //one colour of cubes and armies
	//int* cubes; //armies (starts at 14)
	//int* discs; //cities (starts at 3)
	//int* coins; //8 coins (5), 9 coins (4), 11 coins (3), 14 coins (2)
	//int* bid; //highest number starts the game

	vector<int> bid(int, int);
	int* initializeVectorBid(int);
	int* compareToStart(int);
	int* startingPlayer(int, int);
};

static vector<int> playersBid;
