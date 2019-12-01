#include "PlayerStrategies.h"
#include <iostream>
#include <cstdlib>

int InteractiveHuman::chooseCard() const
{
	int icardPicked;
	std::cout << "\nWhich card are you taking from the hand? " << endl;
	std::cin >> icardPicked;
	icardPicked--;
	return icardPicked;
}

int InteractiveHuman::chooseTargetRegion(string action, Map m) const
{
	int targetRegion;
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

	std::cin >> targetRegion;
	return targetRegion;
}

int InteractiveHuman::chooseToIgnoreAction(string action) const
{

	int answer = -1;

	while (answer != 0 && answer != 1) {
		cout << "Do you want to ignore this action [" << action << "] ?\n For yes enter 1, for no enter 0.";
		cin >> answer;
	}
	return answer;
}

int InteractiveHuman::chooseDestinationRegion(string action) const
{
	int destinationRegion;
	if (action.at(0) == 'M') {
		cout << "\n\nTo which region do you want to move your army?\nGive the region's ID.: ";
	}
	else if (action.at(0) == 'S') {
		cout << "\n\nTo which region do you want to move your army?\nGive the region's ID.: ";
	}

	std::cin >> destinationRegion;
	return destinationRegion;

}

int InteractiveHuman::choosePlayerToDestroyArmy() const
{

	int playerID;
	cout << "\n\nFor which player do you want to destroy an army?\nGive the Player's ID.";
	std::cin >> playerID;
	return playerID;
}

int InteractiveHuman::chooseNumberOfArmyToMove(string action) const
{
	int numberArmy;
	if (action.at(0) == 'M') {
		cout << "\n\nEnter the number of armies you want to move: ";
	}
	else {
		cout << "\n\nEnter the number of armies you want to move: ";
	}
	std::cin >> numberArmy;
	return numberArmy;
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

int GreedyBot::chooseTargetRegion(string action, Map m) const
{

	int numOfRegions = m.findNbRegions();
	int targetRegion;

	if (action.at(0) == 'B') {
		cout << "\n\nIn which region do you want to build a city?\nGive the region's ID. ";
	}
	else if (action.at(0) == 'D') {
		cout << "\n\nIn which region do you want to destroy an army?\nGive the region's ID. ";

	}
	else {
		//do nothing -> ignore
		targetRegion = -1;
	}


	return 0;
}

int GreedyBot::chooseToIgnoreAction(string action) const
{
	if (action.at(0) != 'B' && action.at(0) != 'D') {

		cout << "This action [" << action << "] will be ignored." << endl;

		return 1;
	}

	return 0;
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

int ModerateBot::chooseTargetRegion(string action, Map m) const
{
	return 0;
}

int ModerateBot::chooseToIgnoreAction(string action) const
{
	if (action.at(0) != 'A' && action.at(0) != 'M') {

		cout << "This action [" << action << "] will be ignored." << endl;

		return 1;
	}

	return 0;
}
