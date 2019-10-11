#include "BiddingFacility.h"
#include <iostream>

using namespace std;

//Player * BiddingFacility::playOrder()
//{
//	return nullptr;
//}

int* BiddingFacility::bid(int coins)
{
	int i;
	std::cout << "How many coins are you bidding?\n";
	std::cin >> i;

	if (i >> coins) {
		std::cout << "You do not have enough coins.";
	}
	else {
		std::cout << "You are bidding: " << i << " coins.\n";
	}

	return nullptr;
}

//std::string * BiddingFacility::playerColor()
//{
//	std::string i;
//	std::cout << "Enter the color you wish to choose\n";
//	std::cin >> i;
//	std::cout << "Your color is now: " << i;
//
//	return 0;
//}
