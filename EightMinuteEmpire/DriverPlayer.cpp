#include "DriverPlayer.h"
#include "Player.h"
#include <list>
#include <iostream>

using namespace std;

void driverPlayerTest()
{
	int numberOfPlayers = 0;
	std::list <Player>* players = new std::list <Player>();

	cout << "How many players are joining the game? ";
	cin >> numberOfPlayers;

	for (int i = 0; i < numberOfPlayers; i++)
	{
		Player* temp = new Player(&numberOfPlayers, (i + 1));

		(*players).push_back(*temp);

	}

	cout << "Demonstrating that each player has regions: \n";

	for (int i = 0; i < 10; i++)
	{

		Region* region = new Region(i, (i + 1) % 2);

		// Create iterator pointing to first element
		std::list<Player>::iterator it = (*players).begin();
		// Advance the iterator by 2 positions,
		std::advance(it, i % numberOfPlayers);

		it->addRegion(region);
	}

	for (int i = 0; i < numberOfPlayers; i++)
	{
		// Create iterator pointing to first element
		std::list<Player>::iterator itP = (*players).begin();
		// Advance the iterator by 2 positions,
		std::advance(itP, i);

		cout << "Player" << (i + 1) << ":\n";

		for (std::list<Region>::iterator it = (*(itP->regionOwned)).begin(); it != (*(itP->regionOwned)).end(); ++it) {
			cout << *(it->val) << "\n";
		}

	}
	Region* region1 = new Region(10, 3);
	Region* region2 = new Region(11, 3);

	cout << "\n\n";

	(*(players->begin())).payCoin(new int(2));
	(*(players->begin())).placeNewArmies(region1, new int(2));
	(*(players->begin())).moveArmies(region1, region2, new int(2));
	(*(players->begin())).moveOverLand(region1, region2, new int(2));
	(*(players->begin())).buildCity(region1);
	(*(players->begin())).destroyArmy(region1, new int(1));
}
