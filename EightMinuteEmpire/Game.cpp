#include "Game.h"
#include "Cards.h"
#include <iostream>
#include <ctime>


int main() {

	MapLoader* mapL = new MapLoader();
	mapL->readFolder("C:\\documents\\Maryam\\fall2019\\comp345\\tryingThisOne\\comp345-eight-minute-empire\\EightMinuteEmpire");
	//add cin to read file name in readfolder
	Map gameMap = mapL->readFile("test2.txt");

	Region startingRegion = gameMap.getStartingRegion();
	std::cout << "gameMap.startingRegion " << gameMap.startingRegion << endl;
	std::cout << "startingRegion " << &startingRegion << endl;
	srand(time(NULL));
	//int numberOfPlayers = 2 + (std::rand() % 4);
	int numberOfPlayers = 2;
	std::cout << "numberOfPlayers " << numberOfPlayers << endl;

	do {
		std::cout << "How many players are joining the game? ";
		std::cin >> numberOfPlayers;
	} while (numberOfPlayers < 2 || numberOfPlayers>5);

	Game myGame(numberOfPlayers, gameMap);


	myGame.startup(startingRegion);

	gameMap.display();

	myGame.gameLoop();

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

	if (n == 2) {
		dummyPlayerExists = true;
		dummyPlayer = new Player(3, 0, -1, Green);
	}
	else {
		dummyPlayerExists = false;
	}

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
		//Player dummyPlayer(3, 0, -1, Green);
		addPlayer(playerOne);
		addPlayer(playerTwo);
		//addPlayer(dummyPlayer);
		playerOne.placeNewArmies(&startingRegion, &numberOfArmies);
		cout << "++++++" << endl;
		startingRegion.display();
		cout << "++++++" << endl;
		playerTwo.placeNewArmies(&startingRegion, &numberOfArmies);
		cout << "++++++" << endl;
		startingRegion.display();
		cout << "++++++" << endl;

		int numberOfDummyArmies = 1;
		for (int i = 0; i < 5; i++) {
			int selectedRegionId = (std::rand() % nbRegion);
			std::cout << selectedRegionId << ", ";
			int j = 0;
			for (std::list<Region>::iterator it = map->eightMinEmpMap->begin(); it != map->eightMinEmpMap->end(); ++it) {
				if (j == selectedRegionId) {
					(*dummyPlayer).placeNewArmies(&(*it), &numberOfDummyArmies);
					break;
				}
				j++;
			}
			selectedRegionId = (std::rand() % nbRegion);
			std::cout << selectedRegionId << ", ";
			j = 0;
			for (std::list<Region>::iterator it = map->eightMinEmpMap->begin(); it != map->eightMinEmpMap->end(); ++it) {
				if (j == selectedRegionId) {
					(*dummyPlayer).placeNewArmies(&(*it), &numberOfDummyArmies);
					break;
				}
				j++;
			}


		}
		std::cout << endl;

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
		if (*(it->playerAge) != -1) {
			playersBid = it->biddingFacility->bid(*(it->tokenCoins), pIndex);
			std::cout << "numberOFCoins: " << *(it->tokenCoins) << endl;
			pIndex++;
		}
	}

	for (int i = 0; i < *numberOfPlayers; i++) {
		std::cout << "\nPlayer " << i + 1 << " bid " << playersBid.operator[](i)
			<< " coins.";
	}

	int max = -1;
	int counter = 0;
	int playerIndexHighestBid = 0;
	vector<int> highestBid;

	for (std::vector<int>::const_iterator i = playersBid.begin(); i != playersBid.end(); ++i) {
		std::cout << "\nPlayer original ****  " << " bid " << *i;
		if (*i > max) {
			max = *i;
		}
	}

	std::cout << "max " << max << std::endl;

	for (std::vector<int>::const_iterator i = playersBid.begin(); i != playersBid.end(); ++i, ++counter) {
		if (*i == max) {
			highestBid.push_back(counter);
		}
	}


	if (highestBid.size() == 1) {
		*startIndex = highestBid.front();
		std::cout << "\n\nPlayer " << highestBid.front() + 1 << " will start the game.";
	}
	else { //more than one player have the highest bid
		int j = 0;
		for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it, ++j) {
			std::cout << "\n\nplayer " << j + 1 << " age: " << *(it->playerAge) << endl;
		}

		int minAge = 999;
		int youngestIndex = 0;
		for (std::vector<int>::const_iterator i = highestBid.begin(); i != highestBid.end(); ++i) {
			std::list<Player>::iterator it = (*players).begin();
			std::advance(it, *i);
			if (minAge > *(it->playerAge)) {
				minAge = *(it->playerAge);
				youngestIndex = *i;
			}
		}
		*startIndex = youngestIndex;
		/*
		int indexCount = 0;
		int youngestAge = 0;

		if (max == 0) {
			std::cout << "\n\nNo players have bid an amount.";

			for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {
				std::cout << "\n\nplayer " << indexCount + 1 << "age: " << *(it->playerAge) << endl;
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
				std::cout << "player " << indexCount + 1 << "age: " << *(it->playerAge) << endl;
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
		*/
		//change here

		std::cout << "\nPlayer " << *startIndex + 1 << " will start the game.\n";

		//remove coins here
		std::list<Player>::iterator it = (*players).begin();
		std::advance(it, *startIndex);
		(*it).payCoin(&max);
		int k = 0;
		for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it, ++k) {
			std::cout << "\n player tokenCoins " << k + 1 << ": " << *(it->tokenCoins) << endl;
		}

	}

}


void Game::gameLoop()
{

	//either while loop or for loop??
	int icardPicked = 0;
	Cards cardPicked;
	int count = 0;
	std::list<Player>::iterator it = (*players).begin();
	std::advance(it, *startIndex % *numberOfPlayers);

	while (count < *numberOfPlayers) {

		std::cout << "\n\n\nIt's " << (*startIndex + count) % *numberOfPlayers << " " << return_value(it->chosenColor) << "'s turn." << endl;
		count++;
		if (count + *startIndex == *numberOfPlayers) {
			it = (*players).begin();
		}
		else {
			std::advance(it, 1);
		}


	}

	while (count < *numberOfPlayers) {

		std::cout << "\n\n\nIt's " << Colors(it->chosenColor) << "'s turn." << endl;
		//TODO display hand
		std::cout << "\nWhich card are you taking from the hand? \n(Please enter the position of the card from left to right by starting the count at 0)" << endl;
		std::cin >> icardPicked;


		cardPicked = cardPicked.exchange(icardPicked); //how to call???? should be static?
		(*it).payCoin(&(cardsCost[icardPicked])); // do a method that matches the position and coins to pay

		cardPicked.displayCardAction();//display

		//do a case action -> call method in player with correct arguments


		count++;
		if (count + *startIndex == *numberOfPlayers) {
			it = (*players).begin();
		}
		else {
			std::advance(it, 1);
		}


	}


}
string Game::return_value(int index)
{
	string temp = "";
	switch (index)
	{
	case 0: temp = "Red";
		break;
	case 1: temp = "Blue";
		break;
	case 2: temp = "Yellow";
		break;
	case 3: temp = "Green";
		break;
	case 4: temp = "White";
		break;
	default:
		break;
	}
	return temp;
}

//bidding doesnt seem to work??