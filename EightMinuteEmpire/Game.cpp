#include "Game.h"
#include <iostream>
#include <ctime>


int main() {

	MapLoader* mapL = new MapLoader();
	mapL->readFolder("C:\\Users\\Maryam\\uni\\FALL19\\COMP 345\\Assignments\\A2\\11032019\\11032019\\directory\\");
	//add cin to read file name in readfolder
	Map gameMap = mapL->readFile("directory\\test2.txt");

	Region startingRegion = gameMap.getStartingRegion();
	std::cout << "gameMap.startingRegion " << gameMap.startingRegion << endl;
	std::cout << "startingRegion " << &startingRegion << endl;
	srand(time(NULL));
	//int numberOfPlayers = 2 + (std::rand() % 4);
	int numberOfPlayers = 2;
	std::cout << "numberOfPlayers " << numberOfPlayers << endl;

	Game myGame(numberOfPlayers, gameMap);

	myGame.gameStart();
	myGame.startup(startingRegion);

	gameMap.display();

	return 0;

}
/*
Game::Game(const Game &g)
{
	*numberOfPlayers = *(g.numberOfPlayers);
	players = g.players;
	map = g.map;
	hand = g.hand;

}
*/

Game::Game(int n, Map pMap)
{
	numberOfPlayers = new int(n);
	players = new std::list<Player>();
	map = &pMap;
	hand = new Hand();
	startIndex = new int(0);

}

Game::~Game()
{
	//delete numberOfPlayers;
}

void Game::addPlayer(Player p)
{
	players->push_back(p);
}

void Game::gameStart() {


	//Select the number of players in the game (2-5)

	do {
		std::cout << "How many players are joining the game? ";
		std::cin >> *numberOfPlayers;
	} while (*numberOfPlayers < 2 || *numberOfPlayers>2);
	for (int i = 0; i < *numberOfPlayers; i++)
	{
		Player* temp = new Player(numberOfPlayers, (i + 1));

		(*players).push_back(*temp);

	}

}


void Game::startup(Region startingRegion)
{
	Cards cardsTesting;
	//Hand  handTesting;
	cardsTesting.initializeDeck(); //Create 42 cards
	cardsTesting.shuffleCards(); //Shuffle cards

	cout << "Hand: \n" << endl;
	for (int i = 0; i < 6; i++) {
		cardsTesting.draw(i); //drawing first 6 cards
		cardsTesting.displayHand(i); //displaying the hand
	}
	//
	int numberOfArmies = 3;
	int nbRegion = map->eightMinEmpMap->size();
	std::cout << "nbRegion " << nbRegion << endl;
	if (2 == *numberOfPlayers) {
		Player playerOne(1, 14, 18 + (std::rand() % 40), Red);
		Player playerTwo(2, 14, 18 + (std::rand() % 40), Blue);
		Player dummyPlayer(3, 0, -1, Green);
		addPlayer(playerOne);
		addPlayer(playerTwo);
		addPlayer(dummyPlayer);
		playerOne.placeNewArmies(&startingRegion, &numberOfArmies);
		cout << "++++++" << endl;
		startingRegion.display();
		cout << "++++++" << endl;
		playerTwo.placeNewArmies(&startingRegion, &numberOfArmies);
		cout << "++++++" << endl;
		startingRegion.display();
		cout << "++++++" << endl;
		/*
		int numberOfDummyArmies = 1;
		for (int i = 0; i < 5; i++) {
			int selectedRegionId = (std::rand() % nbRegion);
			std::cout << selectedRegionId << ", ";
			int j = 0;
			for (std::list<Region>::iterator it = map->eightMinEmpMap->begin(); it != map->eightMinEmpMap->end(); ++it) {
				if (j == selectedRegionId) {
					dummyPlayer.placeNewArmies(&(*it), &numberOfDummyArmies);
					break;
				}
				j++;
			}
			selectedRegionId = (std::rand() % nbRegion);
			std::cout << selectedRegionId << ", ";
			j = 0;
			for (std::list<Region>::iterator it = map->eightMinEmpMap->begin(); it != map->eightMinEmpMap->end(); ++it) {
				if (j == selectedRegionId) {
					dummyPlayer.placeNewArmies(&(*it), &numberOfDummyArmies);
					break;
				}
				j++;
			}


		}
		std::cout << endl;
		*/
	}
	else if (3 == *numberOfPlayers) {
		Player playerOne(1, 11, 18 + (std::rand() % 40), Red);
		Player playerTwo(2, 11, 18 + (std::rand() % 40), Blue);
		Player playerThree(3, 11, 18 + (std::rand() % 40), Green);
		addPlayer(playerOne);
		addPlayer(playerTwo);
		addPlayer(playerThree);
		playerOne.placeNewArmies(&startingRegion, &numberOfArmies);
		playerTwo.placeNewArmies(&startingRegion, &numberOfArmies);
		playerThree.placeNewArmies(&startingRegion, &numberOfArmies);
	}
	else if (4 == *numberOfPlayers) {
		Player playerOne(1, 9, 18 + (std::rand() % 40), Red);
		Player playerTwo(2, 9, 18 + (std::rand() % 40), Blue);
		Player playerThree(3, 9, 18 + (std::rand() % 40), Green);
		Player playerFour(4, 9, 18 + (std::rand() % 40), Yellow);
		addPlayer(playerOne);
		addPlayer(playerTwo);
		addPlayer(playerThree);
		addPlayer(playerFour);
		playerOne.placeNewArmies(&startingRegion, &numberOfArmies);
		playerTwo.placeNewArmies(&startingRegion, &numberOfArmies);
		playerThree.placeNewArmies(&startingRegion, &numberOfArmies);
		playerFour.placeNewArmies(&startingRegion, &numberOfArmies);
	}
	else if (5 == *numberOfPlayers) {
		Player playerOne(1, 8, 18 + (std::rand() % 40), Red);
		Player playerTwo(2, 8, 18 + (std::rand() % 40), Blue);
		Player playerThree(3, 8, 18 + (std::rand() % 40), Green);
		Player playerFour(4, 8, 18 + (std::rand() % 40), Yellow);
		Player playerFive(5, 8, 18 + (std::rand() % 40), White);
		addPlayer(playerOne);
		addPlayer(playerTwo);
		addPlayer(playerThree);
		addPlayer(playerFour);
		addPlayer(playerFive);
		playerOne.placeNewArmies(&startingRegion, &numberOfArmies);
		playerTwo.placeNewArmies(&startingRegion, &numberOfArmies);
		playerThree.placeNewArmies(&startingRegion, &numberOfArmies);
		playerFour.placeNewArmies(&startingRegion, &numberOfArmies);
		playerFive.placeNewArmies(&startingRegion, &numberOfArmies);
	}


	bidding();


}




void Game::bidding() {

	playersBid.resize(*numberOfPlayers);

	int pIndex = 0;
	for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it)
	{

		it->biddingFacility->bid(*(it->tokenCoins), pIndex);

		pIndex++;
	}

	for (int i = 0; i < *numberOfPlayers; i++) {
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


	if (highestBid.size() == 1) {
		*startIndex = highestBid.front();
		std::cout << "\n\nPlayer " << highestBid.front() + 1 << " will start the game.";
	}
	else { //more than one player have the highest bid

		int indexCount = 0;
		int youngestIndex = 0;
		int youngestAge = 0;

		if (max == 0) {
			std::cout << "\n\nNo players have bid an amount.";

			for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {

				if (youngestAge == 0) {
					youngestAge = *(it->playerAge);
					youngestIndex = 0;
				}
				else {
					if (*(it->playerAge) < youngestAge) {
						youngestAge = *(it->playerAge);
						youngestIndex = indexCount;
					}

				}
				indexCount++;

			}

			*startIndex = youngestIndex;

		}
		else {

			std::cout << "\n\nPlayers ";

			for (std::vector<int>::const_iterator i = highestBid.begin(); i != highestBid.end(); ++i)
				std::cout << *i + 1 << ',' << " ";

			std::cout << "have bid the same highest amount.\n";

			for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {
				if ((playersBid.at(indexCount)) == max) {
					if (youngestAge == 0) {
						youngestAge = *(it->playerAge);
						youngestIndex = 0;
					}
					else {
						if (*(it->playerAge) < youngestAge) {
							youngestAge = *(it->playerAge);
							youngestIndex = indexCount;
						}

					}
					indexCount++;
				}
			}
			*startIndex = youngestIndex;

		}

		//change here

		std::cout << "\nPlayer " << startIndex + 1 << " will start the game.\n";
	}

}


void Game::gameLoop()
{



}