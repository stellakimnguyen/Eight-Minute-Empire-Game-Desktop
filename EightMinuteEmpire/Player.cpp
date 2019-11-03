#include "Player.h"
#include <iostream>
using namespace std;

/*
int main() {


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

	return 0;
}
	*/


Player::Player(int* numberOfPlayer, int pn) {
	playerNumber = new int(pn);
	int tempAge = 0;
	cout << "Player " << *playerNumber << ", your age: ";
	cin >> tempAge;
	playerAge = new int(tempAge);
	biddingFacility = new BiddingFacility();
	cubes = new int(14);
	discs = new int(3);

	if (*numberOfPlayer == 5) {
		tokenCoins = new int(8);
	}
	else if (*numberOfPlayer == 4) {
		tokenCoins = new int(9);
	}
	else if (*numberOfPlayer == 3) {
		tokenCoins = new int(11);
	}
	else if (*numberOfPlayer == 2) {
		tokenCoins = new int(14);
	}

	regionOwned = new std::list <Region>();
	cards = new Cards();

}

Player::Player(int pn, int tc, int age, Colors c) {
	playerNumber = new int(pn);
	playerAge = new int(age);
	biddingFacility = new BiddingFacility();
	cubes = new int(14);
	discs = new int(3);

	tokenCoins = new int(tc);
	chosenColor = c;
	regionOwned = new std::list <Region>();
	cards = new Cards();


}

Player::~Player()
{

	//delete the pointers in the constructor

	//delete cubes;
	//delete discs;
	//delete tokenCoins;
	//delete regionOwned;
	//delete biddingFacility;
	//delete cards;


}

void Player::addRegion(Region* regionToAdd)
{
	//for the player, adds the region when they have more than 1 army

	regionOwned->push_back(*regionToAdd);

}

void Player::payCoin(int* value)
{
	cout << "This removes the paid coins from the player's coins." << endl;
	/*

	*tokenCoins = *tokenCoins - *value;

	*/

}
//TODO break out of the if in the for loop
void Player::placeNewArmies(Region* region, int* value)
{
	cout << "This allows a player to place new armies in a certain region." << endl;
	//region->display();
	
	//should we verify that the total number of armies is not surpassing the limit?
	//cout << "cubes " << *cubes << " value " << *value << endl;
	if (*cubes - *value >= 0) {

		bool rOwned = false;
		for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
			if (it->compareRegions(region)) {
				rOwned = true;
				break;
			}
		}
		if (!rOwned) {
			regionOwned->push_back(*region);
		}

		//std::stoi(regCont.find(std::to_string(*(itNeigh->val)))->second;
		std::cout << chosenColor << ": " << region->numberOfArmiesPerPlayer[chosenColor] << ", ";
		std::cout << chosenColor << ": " << region->numberOfArmiesPerPlayer.find(chosenColor)->second << ", ";
		region->numberOfArmiesPerPlayer[chosenColor] = region->numberOfArmiesPerPlayer.find(chosenColor)->second + *value;
		*(region->numberOfArmy) = *(region->numberOfArmy) + *value; // add army to the region
		*cubes = *cubes - *value;
		std::cout << chosenColor << ": " << region->numberOfArmiesPerPlayer[chosenColor] << ", ";
		std::cout << chosenColor << ": " << region->numberOfArmiesPerPlayer.find(chosenColor)->second << ", ";
		std::cout << endl;

	}
	region->display();
	//cout << "end  ---- -This allows a player to place new armies in a certain region." << endl;

}

void Player::moveArmies(Region* regionFrom, Region* regionTo, int* value)
{
	//have to remove the armies from the region where they were and put them in the new region
	cout << "This allows a player to move a number of armies from one region to another." << endl;

	
	if (regionFrom->continent != regionTo->continent) {
		cout << "Can't move armies to another continent!";
	}
	else {

		for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
			if (it->compareRegions(regionFrom)) {
				regionFrom->numberOfArmy = regionFrom->numberOfArmy - *value;

				if (regionFrom->numberOfArmy == 0) {
					//(*regionOwned).remove(*regionFrom);//does this work?? shouldn't be reggionFrom?
				}

			}
		}

		regionOwned->push_back(*regionTo);
		regionTo->numberOfArmy = regionTo->numberOfArmy + *value;
		//no need to change the value of cubes since we're moving armies that were already on the board
		//*cubes = *cubes + *value;

	}
	
}

void Player::moveOverLand(Region* regionFrom, Region* regionTo, int* value)
{
	cout << "This allows a player to move a number of armies from one region to another and he can go over continents." << endl;
	

	for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
		if (it->compareRegions(regionFrom)) {
			regionFrom->numberOfArmy = regionFrom->numberOfArmy - *value;

			if (regionFrom->numberOfArmy == 0) {
				//(*regionOwned).remove(*regionFrom);//does this work??
			}

		}
	}

	regionOwned->push_back(*regionTo);
	regionTo->numberOfArmy = regionTo->numberOfArmy + *value;

	
}

void Player::buildCity(Region* region)
{
	//add a city to the region picked -> region already to the player
	cout << "This adds a city to the region picked by the player, the player must have the region and he can add more than one city." << endl;
	
	if (discs != 0) {

		region->cityNumber = region->cityNumber + 1;

		*discs = *discs - 1;

	}

	

}

void Player::destroyArmy(Region* region, int* value)
{
	//destroy an army from a specific region
	cout << "This removes a number of armies from a specific region for the player." << endl;
	

	if (*cubes != 14) {


		for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
			if (it->compareRegions(region)) {
				region->numberOfArmy = region->numberOfArmy - *value; // remove
			}
		}

		*cubes = *cubes + *value;
	}

	
}

void Player::setChosenColor(Colors c)
{
	chosenColor = c;

}
