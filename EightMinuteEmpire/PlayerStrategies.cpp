#include "PlayerStrategies.h"
#include <iostream>
#include <cstdlib>
#include "Utility.h"

InteractiveHuman::InteractiveHuman(int np) : PlayerStrategies(np)
{
}

int InteractiveHuman::chooseCard() const
{
	int icardPicked;
	std::cout << "\nWhich card are you taking from the hand? " << endl;
	//std::cin >> icardPicked;

	inputHandling(&icardPicked, 1, 6);

	icardPicked--;
	return icardPicked;
}

int InteractiveHuman::chooseTargetRegion(string action, Map m, int numberOfArmiesToMove) const
{
	int targetRegion;
	int totalNbRegions = m.findNbRegions();

	if (action.at(0) == 'A') {
		std::cout << "\n\nIn which region do you want to add soldiers?\nGive the region's ID. ";
	}
	else if (action.at(0) == 'M') {
		cout << "\n\nFrom which region do you want to move your army?\nGive the region's ID. ";
	}
	else if (action.at(0) == 'S') {
		cout << "\n\nFrom which region do you want to move your army?\nGive the region's ID. ";
	}
	else if (action.at(0) == 'B') {
		cout << "\n\nIn which region do you want to build a city?\nGive the region's ID. ";
	}
	else if (action.at(0) == 'D') {
		cout << "\n\nIn which region do you want to destroy an army?\nGive the region's ID. ";
	}

	inputHandling(&targetRegion, 1, totalNbRegions);

	//std::cin >> targetRegion;
	return targetRegion;
}

int InteractiveHuman::chooseToIgnoreAction(string action) const
{
	int answer = -1;

	cout << "Do you want to ignore this action [" << action << "] ?\n For yes enter 1, for no enter 0.";
	inputHandling(&answer, 0, 1);

	return answer;
}

int InteractiveHuman::chooseDestinationRegion(string action, Map m, int fromRegion) const
{
	int destinationRegion;
	bool acceptableInput;

	if (action.at(0) == 'M') {
		cout << "\n\nTo which region do you want to move your army?\nGive the region's ID.: ";
	}
	else if (action.at(0) == 'S') {
		cout << "\n\nTo which region do you want to move your army?\nGive the region's ID.: ";
	}

	//std::cin >> destinationRegion;
	//Handle inputs other than int
	do {
		try {
			std::cin >> destinationRegion;
			acceptableInput = true;
			if (std::cin.fail()) { //cin in fail state
				acceptableInput = false;
				std::cin.clear(); //get rid of fail state
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard 'bad' characters
				throw std::string("\nInput not recognized. Please try again.\nNew input: ");
			}
		}
		catch (std::string e) {
			std::cout << e;
		}
	} while (!acceptableInput);

	return destinationRegion;

}

int InteractiveHuman::choosePlayerToDestroyArmy(int numberOfPlayers) const
{

	int playerID;
	cout << "\n\nFor which player do you want to destroy an army?\nGive the Player's ID.";
	std::cin >> playerID;
	return playerID;
}

int InteractiveHuman::chooseNumberOfArmyToMove(int numberOfArmiesLeftToMove) const
{
	int numberArmy;
	bool acceptableInput;
	//if (action.at(0) == 'M') {
		cout << "\n\nEnter the number of armies you want to move: ";
	/*}
	else {
		cout << "\n\nEnter the number of armies you want to move: ";
	}*/
	//std::cin >> numberArmy;

	do {
		try {
			std::cin >> numberArmy;
			acceptableInput = true;
			if (std::cin.fail()) { //cin in fail state
				acceptableInput = false;
				std::cin.clear(); //get rid of fail state
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard 'bad' characters
				throw std::string("\nInput not recognized. Please try again.\nNew input: ");
			}
		}
		catch (std::string e) {
			std::cout << e;
		}
	} while (!acceptableInput);

	return numberArmy;
}

GreedyBot::GreedyBot(int np) : PlayerStrategies(np)
{
}

int GreedyBot::chooseCard() const
{
	int destroyIndex = -1;
	int buildIndex = -1;
	for (int i = 0; i < 6; i++) {
		if (hand[i].singleAction.action.compare("DESTROY") == 0 && destroyIndex == -1) {
			destroyIndex = i;
		}
		if (hand[i].singleAction.action.compare("BUILD") == 0 && buildIndex == -1) {
			buildIndex = i;
		}
	}
	if (destroyIndex == -1 && buildIndex == -1) {
		return -1;
	}
	else if (destroyIndex == -1) {
		return buildIndex;
	}
	else if (buildIndex == -1) {
		return destroyIndex;
	}
	else{
		if (rand() % 2 == 0) {
			return destroyIndex;
		}
		else {
			return buildIndex;
		}
	}

}

int GreedyBot::chooseTargetRegion(string action, Map m, int numberOfArmiesToMove) const
{

	int numOfRegions = m.findNbRegions();
	int targetRegion = -1;

	if (action.at(0) == 'A') {
		for (std::list<Region>::iterator it = (*(m.eightMinEmpMap)).begin(); it != (*(m.eightMinEmpMap)).end(); ++it) {

			if (*(it->regionOwner) == playerNumber) {
				targetRegion = *(it->val);
				break;

			}
			if ((*it).compareRegions((m.getStartingRegion())) || it->numberOfCityPerPlayer.find((Colors)playerNumber)->second >= numberOfArmiesToMove) {
				targetRegion = *(it->val);
				break;
			}

		}
	}
	else if (action.at(0) == 'B') {
		for (std::list<Region>::iterator it = (*(m.eightMinEmpMap)).begin(); it != (*(m.eightMinEmpMap)).end(); ++it) {

			if (*(it->regionOwner) == playerNumber && *(m.startingRegion->val) != *(it->val)) {
				targetRegion = *(it->val);
				break;
			}
			if (it->numberOfCityPerPlayer.find((Colors)playerNumber)->second >= numberOfArmiesToMove) {
				targetRegion = *(it->val);
				break;
			}
		}
	}
	else if (action.at(0) == 'D') {
		for (std::list<Region>::iterator it = (*(m.eightMinEmpMap)).begin(); it != (*(m.eightMinEmpMap)).end(); ++it) {

			if (*(it->regionOwner) != playerNumber && it->numberOfArmiesPerPlayer.find((Colors) *(it->regionOwner))->second>=1) {
				targetRegion = *(it->val);
				break;

			}

		}
	}
	else {
		//do nothing -> ignore
		targetRegion = -1;
	}


	return targetRegion;
}

int GreedyBot::chooseToIgnoreAction(string action) const
{
	if (action.at(0) != 'B' && action.at(0) != 'D') {

		cout << "This action [" << action << "] will be ignored." << endl;

		return 1;
	}

	return 0;
}

int GreedyBot::chooseDestinationRegion(string action, Map m, int fromRegion) const
{
	int destinationRegion = -1;
	Region* rFrom = m.findRegion(fromRegion);

	if (action.at(0) == 'M') {
		for (std::list<Region>::iterator it = (*(m.eightMinEmpMap)).begin(); it != (*(m.eightMinEmpMap)).end(); ++it) {

			if (*(it->regionOwner) == playerNumber && *(it->val) != fromRegion) {
				destinationRegion = *(it->val);
				break;
			}
			if (*(it->val) != fromRegion && *(it->continent) == *(rFrom->continent)) {
				destinationRegion = *(it->val);
				break;
			}

		}
	}
	else if (action.at(0) == 'S') {
		for (std::list<Region>::iterator it = (*(m.eightMinEmpMap)).begin(); it != (*(m.eightMinEmpMap)).end(); ++it) {

			if (*(it->regionOwner) == playerNumber && *(it->val) != fromRegion) {
				destinationRegion = *(it->val);
				break;
			}
			if (*(it->val) != fromRegion && *(it->continent) != *(rFrom->continent)) {
				destinationRegion = *(it->val);
				break;
			}

		}
	}
	else {
		//do nothing -> ignore
		destinationRegion = -1;
	}

	return destinationRegion;
}

int GreedyBot::choosePlayerToDestroyArmy(int numberOfPlayers) const
{
	int playerID;
	do {
		playerID = 1 + (std::rand() % numberOfPlayers);
	} while (playerID == playerNumber);
	
	return playerID;
}

int GreedyBot::chooseNumberOfArmyToMove(int numberOfArmiesLeftToMove) const
{
	return 1 + (std::rand() % numberOfArmiesLeftToMove);
}

ModerateBot::ModerateBot(int np) : PlayerStrategies(np)
{
}

int ModerateBot::chooseCard() const
{
	int addIndex = -1;
	int moveIndex = -1;
	for (int i = 0; i < 6; i++) {
		if (hand[i].singleAction.action.compare("ADD") == 0 && addIndex == -1) {
			addIndex = i;
		}
		if (hand[i].singleAction.action.compare("MOVE") == 0 && moveIndex == -1) {
			moveIndex = i;
		}
	}
	if (addIndex == -1 && moveIndex == -1) {
		return -1;
	}
	else if (addIndex == -1) {
		return moveIndex;
	}
	else{
		return addIndex;
	}
}

int ModerateBot::chooseTargetRegion(string action, Map m, int numberOfArmiesToMove) const
{
	int numOfRegions = m.findNbRegions();
	int targetRegion = -1;

	if (action.at(0) == 'A') {
		for (std::list<Region>::iterator it = (*(m.eightMinEmpMap)).begin(); it != (*(m.eightMinEmpMap)).end(); ++it) {

			if (*(it->regionOwner) == playerNumber) {
				targetRegion = *(it->val);
				break;

			}
			if ((*it).compareRegions((m.getStartingRegion())) || it->numberOfCityPerPlayer.find((Colors)playerNumber)->second >= 1) {
				targetRegion = *(it->val);
				break;
			}

		}
	}
	else if (action.at(0) == 'M' || action.at(0) == 'S') {
		for (std::list<Region>::iterator it = (*(m.eightMinEmpMap)).begin(); it != (*(m.eightMinEmpMap)).end(); ++it) {

			if (*(it->regionOwner) == playerNumber) {
				targetRegion = *(it->val);
				break;

			}
			if (it->numberOfArmiesPerPlayer.find((Colors)playerNumber)->second >= numberOfArmiesToMove) {
				targetRegion = *(it->val);
				break;
			}

		}
	}
	else {
		//do nothing -> ignore
		targetRegion = -1;
	}


	return targetRegion;
}

int ModerateBot::chooseToIgnoreAction(string action) const
{
	if (action.at(0) != 'A' && action.at(0) != 'M') {

		cout << "This action [" << action << "] will be ignored." << endl;

		return 1;
	}

	return 0;
}

int ModerateBot::chooseDestinationRegion(string action, Map m, int fromRegion) const
{
	int destinationRegion = -1;
	Region* rFrom = m.findRegion(fromRegion);

	if (action.at(0) == 'M') {
		for (std::list<Region>::iterator it = (*(m.eightMinEmpMap)).begin(); it != (*(m.eightMinEmpMap)).end(); ++it) {

			if (*(it->regionOwner) == playerNumber && *(it->val) != fromRegion) {
				destinationRegion = *(it->val);
				break;
			}
			if (*(it->val) != fromRegion && *(it->continent) == *(rFrom->continent)) {
				destinationRegion = *(it->val);
				break;
			}

		}
	}
	else if (action.at(0) == 'S') {
		for (std::list<Region>::iterator it = (*(m.eightMinEmpMap)).begin(); it != (*(m.eightMinEmpMap)).end(); ++it) {

			if (*(it->regionOwner) == playerNumber && *(it->val) != fromRegion) {
				destinationRegion = *(it->val);
				break;
			}
			if (*(it->val) != fromRegion && *(it->continent) != *(rFrom->continent)) {
				destinationRegion = *(it->val);
				break;
			}

		}
	}
	else {
		//do nothing -> ignore
		destinationRegion = -1;
	}

	return destinationRegion;
}

int ModerateBot::choosePlayerToDestroyArmy(int numberOfPlayers) const
{
	int playerID;
	do {
		playerID = 1 + (std::rand() % numberOfPlayers);
	} while (playerID == playerNumber);

	return playerID;
}

int ModerateBot::chooseNumberOfArmyToMove(int numberOfArmiesLeftToMove) const
{
	return 1 + (std::rand() % numberOfArmiesLeftToMove);
}

PlayerStrategies::PlayerStrategies(int pn)
{
	playerNumber = pn;
}
