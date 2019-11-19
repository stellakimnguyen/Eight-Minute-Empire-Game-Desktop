#include "Player.h"
#include <string>
#include <iostream>
#include <algorithm>
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
	cards = cards;

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
	cards = cards;


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
	//cout << "This removes the paid coins from the player's coins." << endl;

	cout << "Number of coins before paying: " << *tokenCoins;

	*tokenCoins = *tokenCoins - *value;

	cout << "Number of coins left: " << *tokenCoins;

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
				regionFrom->numberOfArmiesPerPlayer[chosenColor] = regionFrom->numberOfArmiesPerPlayer[chosenColor] - *value;

				if (regionFrom->numberOfArmiesPerPlayer[chosenColor] == 0) {
					(*regionOwned).remove(*regionFrom);

				}

				break;

			}
		}

		regionOwned->push_back(*regionTo);
		regionTo->numberOfArmiesPerPlayer[chosenColor] = regionTo->numberOfArmiesPerPlayer[chosenColor] + *value;
		//no need to change the value of cubes since we're moving armies that were already on the board
		//*cubes = *cubes + *value;

	}

}

void Player::moveOverLand(Region* regionFrom, Region* regionTo, int* value)
{
	cout << "This allows a player to move a number of armies from one region to another and he can go over continents." << endl;


	for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
		if (it->compareRegions(regionFrom)) {
			regionFrom->numberOfArmiesPerPlayer[chosenColor] = regionFrom->numberOfArmiesPerPlayer[chosenColor] - *value;

			if (regionFrom->numberOfArmiesPerPlayer[chosenColor] == 0) {
				(*regionOwned).remove(*regionFrom);
			}
			break;
		}
	}

	regionOwned->push_back(*regionTo);
	regionTo->numberOfArmiesPerPlayer[chosenColor] = regionTo->numberOfArmiesPerPlayer[chosenColor] + *value;


}

void Player::buildCity(Region* region)
{
	//add a city to the region picked -> region already to the player
	cout << "This adds a city to the region picked by the player, the player must have the region and he can add more than one city." << endl;

	if (discs != 0) {

		for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
			if (it->compareRegions(region)) {


				region->numberOfCityPerPlayer[chosenColor] = region->numberOfCityPerPlayer[chosenColor] + 1;

				*discs = *discs - 1;

				break;
			}
		}
	}



}

void Player::destroyArmy(Region* region, int* value)
{
	//destroy an army from a specific region
	cout << "This removes a number of armies from a specific region for the player." << endl;


	if (*cubes != 14) {


		for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
			if (it->compareRegions(region)) {
				region->numberOfArmiesPerPlayer[chosenColor] = region->numberOfArmiesPerPlayer[chosenColor] - *value; // remove
				break;
			}
		}

		*cubes = *cubes + *value;
	}


}

void Player::setChosenColor(Colors c)
{
	chosenColor = c;

}

void Player::ignore() {

}

void Player::takeCard(Cards chosenCard)
{
	(*cards).push_back(chosenCard);
	displayCardsInHand();
	//chosenCard.singleAction.display();
}

void Player::displayCardsInHand() {
	cout << "\n\nYour hand: \n";
	cout << "------------" << endl;
	for (std::list <Cards>::const_iterator i = (*cards).begin(); i != (*cards).end(); ++i) {

		cout << "Action: " << (*i).singleAction.action << "\tAmount: " << (*i).singleAction.amount;
		cout << "\n------------" << endl;
	}
}

void Player::categorizeGoods(string good) {
	if (good == "FOREST") {
		goodsNumber[0] += 1;
	}
	else if (good == "CARROT") {
		goodsNumber[1] += 1;
	}
	else if (good == "ANVIL") {
		goodsNumber[2] += 1;
	}
	else if (good == "ORE") {
		goodsNumber[3] += 1;
	}
	else if (good == "CRYSTAL") {
		goodsNumber[4] += 1;
	}
}

void Player::findNbArmiesPerRegion(int totalNbRegions)
{
	nbArmiesAndCitiesPerRegion.resize(totalNbRegions, 0); //initializing all elements to 0

	for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
		nbArmiesAndCitiesPerRegion.at((*(it->val))-1) = it->numberOfArmiesPerPlayer.find(chosenColor)->second;
		nbArmiesAndCitiesPerRegion.at((*(it->val)) - 1) += it->numberOfCityPerPlayer.find(chosenColor)->second;

		*totalNbArmies += it->numberOfArmiesPerPlayer.find(chosenColor)->second;
	}
}

int Player::computeScore(vector<int> finalRegionControllers, int playerNumber) //regions, continents, goods
{
	*nbControllingRegions = 0;

	//regions: more armies in region than any other player on region
	for (int i = 0; i < finalRegionControllers.size(); i++) {
		if (finalRegionControllers.at(i) == playerNumber) {
			score++; //adds one point per regions they control
			*nbControllingRegions++;
		}
	}

	//GOODS: points differ according to good (can choose where the wild card goes)
	cout << "Your current cards: \n" << endl;

	for (std::list <Cards>::const_iterator i = (*cards).begin(); i != (*cards).end(); ++i) {
		cout << "\n" << (*i).good << endl;
		//(*i).singleAction.display();
		SingleAction currentCard = (i->singleAction);
		currentCard.display();
	}

	for (std::list <Cards>::const_iterator i = (*cards).begin(); i != (*cards).end(); ++i) {
		if ((*i).good == "WILD") {
			string wildValue;
			cout << "You have a wild card. To what good would you like to associate with?\n"
				<< "FOREST | CARROT | ANVIL | ORE | CRYSTAL" << endl;
			cin >> wildValue;

			categorizeGoods(wildValue);
		}
		else {
			categorizeGoods((*i).good);
		}
	}

	switch (goodsNumber[0]) { //forest points
	case 2:
	case 3: score += 1;
		break;
	case 4:
	case 5: score += 2;
		break;
	case 6: score += 3;
		break;
	case 7: 
	case 8: score += 5;
		break;
	default: score =+ 0;
	}

	switch (goodsNumber[1]) { //carrot points
	case 3:
	case 4: score += 1;
		break;
	case 5:
	case 6: score += 2;
		break;
	case 7: score += 3;
		break;
	case 8:
	case 9:
	case 10: score += 5;
		break;
	default: score += 0;
	}

	switch (goodsNumber[2]) { //anvil points
	case 2:
	case 3: score += 1;
		break;
	case 4:
	case 5: score += 2;
		break;
	case 6: score += 3;
		break;
	case 7:
	case 8:
	case 9: score += 5;
		break;
	default: score += 0;
	}

	switch (goodsNumber[3]) { //ore points
	case 2: score += 1;
		break;
	case 3: score += 2;
		break;
	case 4: score += 3;
		break;
	case 5:
	case 6:
	case 7: score += 5;
		break;
	default: score += 0;
	}

	switch (goodsNumber[4]) { //crystal points
	case 1: score += 1;
		break;
	case 2: score += 2;
		break;
	case 3: score += 3;
		break;
	case 4:
	case 5: score += 4;
		break;
	default: score += 0;
	}
	
	return score;
}
