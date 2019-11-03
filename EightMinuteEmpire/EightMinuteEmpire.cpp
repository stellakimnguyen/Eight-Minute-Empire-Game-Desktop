// EightMinuteEmpire.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "BiddingFacility.h"
#include "Cards.h"
#include "DriverCards.h"

using namespace std;

int main2()
{
	//INITIALIZING NUMBER OF PLAYERS
	int numPlayers;
	std::cout << "How many players are you?\n";
	std::cin >> numPlayers;

	while (numPlayers <= 1 || numPlayers > 5) {
		if (numPlayers <= 1) {
			std::cout << "\nNot enough players. Please try again.\n"
				<< "How many players are you?\n";
			std::cin >> numPlayers;
		}
		if (numPlayers > 5) {
			std::cout << "\nToo many players. You cannot be more than 5.\n"
				<< "Please try again.\n"
				<< "How many players are you?\n";
			std::cin >> numPlayers;
		}
	}

	//CARDS
	DriverCards driverCards;
	driverCards.driverCardsTest();

	//BIDDING FACILITY
	int initialCoins;
	BiddingFacility bidding;

	bidding.initializeVectorBid(numPlayers);

	switch (numPlayers) {
	case 2: initialCoins = 14;
		break;
	case 3: initialCoins = 11;
		break;
	case 4: initialCoins = 9;
		break;
	case 5: initialCoins = 8;
		break;
	}

	for (int i = 0; i < numPlayers; i++) {
		bidding.bid(initialCoins, i);
	}

	bidding.compareToStart(numPlayers);

	return 0;
};