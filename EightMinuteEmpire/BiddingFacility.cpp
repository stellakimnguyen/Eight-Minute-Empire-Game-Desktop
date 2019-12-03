#include "BiddingFacility.h"
#include <iostream>
#include "Utility.h"

using namespace std;

vector<int> BiddingFacility::bid(int coins, int playerNumber)
{
	std::cout << "\n\nPLAYER " << playerNumber + 1 << "\n"
		<< "--------------------------------";

	int bid;
	std::cout << "\nHow many coins are you bidding?\n";
	/*std::cin >> bid;

	while (bid > coins) {
		std::cout << "You do not have enough coins.\n\n"
			<< "Please enter a different amount.\n";
		std::cin >> bid;
	}*/

	inputHandling(&bid, 0, coins);

	std::cout << "\nYou are bidding: " << bid << " coins.\n";

	playersBid.push_back(bid);

	for (std::vector<int>::const_iterator i = playersBid.begin(); i != playersBid.end(); ++i) {
		//std::cout << "\n BiddingFacility original ****  " << " bid " << *i;
	}

	//playersBid.operator[](playerNumber) = bid;

	////PRINTING OUT VECTOR
	//for (std::vector<int>::const_iterator i = playersBid.begin(); i != playersBid.end(); ++i)
	//	std::cout << *i << ' ';

	return playersBid;
}

int* BiddingFacility::initializeVectorBid(int numPlayers)
{
	playersBid.resize(numPlayers);

	return nullptr;
}

int* BiddingFacility::compareToStart(int numPlayers)
{
	for (int i = 0; i < numPlayers; i++) {
		std::cout << "\nPlayer " << i + 1 << " bid " << playersBid.operator[](i)
			<< " coins.";
	}

	int max = 0;
	int counter = 0;
	vector<int> highestBid;

	for (std::vector<int>::const_iterator i = playersBid.begin(); i != playersBid.end(); ++i, ++counter) {
		if (*i > max) {
			max = *i;
			highestBid.resize(1);
			highestBid.front() = counter;
		}
		else if (*i == max) {
			highestBid.push_back(counter);
		}
	}

	//STARTING PLAYER
	int firstPlayer;

	if (highestBid.size() == 1) {
		firstPlayer = highestBid.front();
		std::cout << "\n\nPlayer " << highestBid.front() + 1 << " will start the game.";
	}
	else { //more than one player have the highet bid
		if (max == 0) {
			std::cout << "\n\nNo players have bid an amount.";
		}
		else {

			std::cout << "\n\nPlayers ";

			for (std::vector<int>::const_iterator i = highestBid.begin(); i != highestBid.end(); ++i)
				std::cout << *i + 1 << ',' << " ";

			std::cout << "have bid the same highest amount.\n";

		}

		std::cout << "\nBetween the players, who is the youngest?\n"
			<< "PLAYER: ";
		std::cin >> firstPlayer;
		std::cout << "\nPlayer " << firstPlayer << " will start the game.\n";
		firstPlayer -= 1;
	}

	startingPlayer(firstPlayer, playersBid.operator[](firstPlayer));

	return nullptr;
}

int* BiddingFacility::startingPlayer(int playerIndex, int bidAmount)
{
	//set playerIndex's player as first player
	//clockwise rotation for the turns: increment by 1 for each turns
	//remove bidAmount from playerIndex's player coins
	//add bidAmount to supply
	return nullptr;
}
