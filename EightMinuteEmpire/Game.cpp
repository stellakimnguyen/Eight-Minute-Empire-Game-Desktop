#include "Game.h"
#include "Cards.h"
#include <iostream>
#include <ctime>


int main() {

// -----
	std::cout << "Which file do you want to use as the map?\n\n";

	std::string fileRead;
	MapLoader* mapL = new MapLoader();
	mapL->readFolder("C:\\documents\\Maryam\\fall2019\\comp345\\20191116\\11032019\\directory");
	//add cin to read file name in readfolder
	//cin >> fileRead;

	//fileRead = "directory\\" + fileRead;
	//Map gameMap = mapL->readFile(fileRead);
	Map* gameMap = mapL->readFile("directory\\goodMap1.txt");
	//Map* gameMap2 = mapL->readFile("directory\\goodMap1.txt");


	Region* startingRegion = gameMap->getStartingRegion();
	std::cout << "gameMap.startingRegion " << gameMap->startingRegion << endl;
	std::cout << "startingRegion " << startingRegion << endl;
	srand(time(NULL));
	//int numberOfPlayers = 2 + (std::rand() % 4);
	int numberOfPlayers = 2;
	std::cout << "numberOfPlayers " << numberOfPlayers << endl;

	do {
		std::cout << "How many players are joining the game? ";
		std::cin >> numberOfPlayers;

		if (numberOfPlayers < 2) {
			cout << "Not enough players. Please try again.\n" << endl;
		}
		else if (numberOfPlayers > 5) {
			cout << "Too many players. Please try again.\n" << endl;
		}
	} while (numberOfPlayers < 2 || numberOfPlayers > 5);

	Game myGame(numberOfPlayers, *gameMap);
	ObserverView ov(&myGame, 1);
	myGame.setView(&ov);

	myGame.startup(startingRegion, *gameMap);

	gameMap->display();

	int currentRoundNum = 0;
	while (currentRoundNum < *(myGame.numberOfRounds)) {
		cout << "\n\n*-*-*-*-*-*-*-*-*\n\n";
		cout << " ROUND NUMBER: " << currentRoundNum + 1;
		cout << "\n\n*-*-*-*-*-*-*-*-*\n";
		myGame.gameLoop(*gameMap);
		currentRoundNum++;

		//move out of loop, here for test only
		myGame.compareScore2(*gameMap);
	}
	
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
	numberOfRounds = new int(findNumberOfRounds(n));
	players = new std::list<Player>();
	map = &pMap;
	hand = new Hand();
	startIndex = new int(0);
	selectedCardIndex = new int(-1);
	supply = new int(0);

}

int Game::findNumberOfRounds(int n) {
	if (n == 2) {
		return 13;
	}
	else if (n == 3) {
		return 10;
	}
	else if (n == 4) {
		return 8;
	}
	else if (n == 5) {
		return 7;
	}
	else {
		return 0;
	}
}

Game::~Game()
{
	//delete numberOfPlayers;
}

void Game::addPlayer(Player* p)
{
	cout << "Game::addPlayer ******************  " << p << " " << *(p->tokenCoins) << endl;
	players->push_back(*p);
	cout << "Game::addPlayer ******************  " << &(players->back()) << " " << *(p->tokenCoins) << endl;
}



void Game::startup(Region* startingRegion, Map gameMap)
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
		Player* playerOne = new Player(1, 14, 18 + (std::rand() % 40), Red);
		Player* playerTwo = new Player(2, 14, 18 + (std::rand() % 40), Blue);
		//Player dummyPlayer(3, 0, -1, Green);
		addPlayer(playerOne);
		addPlayer(playerTwo);
		//addPlayer(dummyPlayer);
		playerOne->placeNewArmies(startingRegion, &numberOfArmies);
		//cout << "++++++" << endl;
		//(*startingRegion).display();
		//cout << "++++++" << endl;
		//playerTwo.placeNewArmies(startingRegion, &numberOfArmies);
		//cout << "++++++" << endl;
		//(*startingRegion).display();
		//cout << "++++++" << endl;

		int numberOfDummyArmies = 1;
		int selectedRegionId = 0;
		Region* reg;
		bool validRegion = false;
		//same as placenewarmies action only remove the constraint of having a city or SR
		for (int i = 0; i < 5; i++) {

			validRegion = false;
			gameMap.display();
			while (!validRegion) {
				cout << "\n\nPlayer 1, In which region do you want to add a soldier?\nGive the region's ID.";
				std::cin >> selectedRegionId;

				for (std::list<Region>::iterator it = (*(gameMap.eightMinEmpMap)).begin(); it != (*(gameMap.eightMinEmpMap)).end(); ++it) {

					if (*(it->val) == selectedRegionId) {

						reg = new Region(*it);
						(*dummyPlayer).placeNewArmies(&(*it), &numberOfDummyArmies);
						validRegion = true;
						break;

					}
					else {
						validRegion = false;
					}

				}

			}
			validRegion = false;
			gameMap.display();
			while (!validRegion) {
				cout << "\n\nPlayer 2, In which region do you want to add a soldier?\nGive the region's ID.";
				std::cin >> selectedRegionId;

				for (std::list<Region>::iterator it = (*(gameMap.eightMinEmpMap)).begin(); it != (*(gameMap.eightMinEmpMap)).end(); ++it) {

					if (*(it->val) == selectedRegionId) {

						reg = new Region(*it);
						(*dummyPlayer).placeNewArmies(&(*it), &numberOfDummyArmies);
						validRegion = true;
						break;

					}
					else {
						validRegion = false;
					}

				}

			}



			/*int selectedRegionId = (std::rand() % nbRegion);
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
			}*/


		}
		std::cout << endl;

	}
	else if (3 == *numberOfPlayers) {
		Player* playerOne = new Player(1, 11, 18 + (std::rand() % 40), Red);
		Player* playerTwo = new Player(2, 11, 18 + (std::rand() % 40), Blue);
		Player* playerThree = new Player(3, 11, 18 + (std::rand() % 40), Green);
		addPlayer(playerOne);
		addPlayer(playerTwo);
		addPlayer(playerThree);
		playerOne->placeNewArmies(startingRegion, &numberOfArmies);
		playerTwo->placeNewArmies(startingRegion, &numberOfArmies);
		playerThree->placeNewArmies(startingRegion, &numberOfArmies);
	}
	else if (4 == *numberOfPlayers) {
		Player* playerOne = new Player(1, 9, 18 + (std::rand() % 40), Red);
		Player* playerTwo = new Player(2, 9, 18 + (std::rand() % 40), Blue);
		Player* playerThree = new Player(3, 9, 18 + (std::rand() % 40), Green);
		Player* playerFour = new Player(4, 9, 18 + (std::rand() % 40), Yellow);
		addPlayer(playerOne);
		addPlayer(playerTwo);
		addPlayer(playerThree);
		addPlayer(playerFour);
		playerOne->placeNewArmies(startingRegion, &numberOfArmies);
		playerTwo->placeNewArmies(startingRegion, &numberOfArmies);
		playerThree->placeNewArmies(startingRegion, &numberOfArmies);
		playerFour->placeNewArmies(startingRegion, &numberOfArmies);
	}
	else if (5 == *numberOfPlayers) {
		Player* playerOne = new Player(1, 8, 18 + (std::rand() % 40), Red);
		Player* playerTwo = new Player(2, 8, 18 + (std::rand() % 40), Blue);
		Player* playerThree = new Player(3, 8, 18 + (std::rand() % 40), Green);
		Player* playerFour = new Player(4, 8, 18 + (std::rand() % 40), Yellow);
		Player* playerFive = new Player(5, 8, 18 + (std::rand() % 40), White);
		addPlayer(playerOne);
		addPlayer(playerTwo);
		addPlayer(playerThree);
		addPlayer(playerFour);
		addPlayer(playerFive);
		playerOne->placeNewArmies(startingRegion, &numberOfArmies);
		playerTwo->placeNewArmies(startingRegion, &numberOfArmies);
		playerThree->placeNewArmies(startingRegion, &numberOfArmies);
		playerFour->placeNewArmies(startingRegion, &numberOfArmies);
		playerFive->placeNewArmies(startingRegion, &numberOfArmies);
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
		//std::cout << "\nPlayer original ****  " << " bid " << *i;
		if (*i > max) {
			max = *i;
		}
	}

	//std::cout << "max " << max << std::endl;

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
		//for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it, ++j) {
		//	std::cout << "\n\nplayer " << j + 1 << " age: " << *(it->playerAge) << endl;
		//}

		int minAge = 999;
		int youngestIndex = 0;
		for (std::vector<int>::const_iterator i = highestBid.begin(); i != highestBid.end(); ++i) {
			std::list<Player>::iterator it = (*players).begin();
			std::advance(it, *i);
			if (minAge > * (it->playerAge)) {
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
		supply = &max;
		int k = 0;
		for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it, ++k) {
			std::cout << "\n player tokenCoins " << k + 1 << ": " << *(it->tokenCoins) << endl;
		}

	}

}


void Game::gameLoop(Map gameMap)
{

	//either while loop or for loop??
	int icardPicked = 0;
	Cards cardPicked;
	int count = 0;
	std::list<Player>::iterator it = (*players).begin();
	std::advance(it, *startIndex % *numberOfPlayers);

	//while (count < *numberOfPlayers) {

	//	std::cout << "\n\n\nIt's Player " << ((*startIndex + count) % *numberOfPlayers) + 1 << "'s [" << return_value(it->chosenColor) << "] turn." << endl;
	//	count++;
	//	if (count + *startIndex == *numberOfPlayers) {
	//		it = (*players).begin();
	//	}
	//	else {
	//		std::advance(it, 1);
	//	}


	//}

	while (count < *numberOfPlayers) {

		std::cout << "\n\n\nIt's Player " << ((*startIndex /*+ count*/) % *numberOfPlayers) + 1 << "'s [" << return_value(it->chosenColor) << "] turn." << endl;
		//TODO display hand
		cardPicked.displayFullHand();

		//std::cout << "\nWhich card are you taking from the hand? " << endl;
		//std::cin >> icardPicked;
		icardPicked = it->choose_Card();

		*(selectedCardIndex) = icardPicked;

		cardPicked = cardPicked.exchange(icardPicked); //could be static?
		(*it).payCoin(&(cardsCost[icardPicked])); //player pays coins

		cardPicked.displayCardAction();//display
		cardPicked.isTaken = true;
		//add card to player cards
		(*it).takeCard(cardPicked);
		//cout << "before action" << endl;
		//do a case action -> call method in player with correct arguments

		int ignoreValue = it->choose_to_ignore_action(cardPicked.singleAction.action);
		if (ignoreValue == 0) {
			convertPlayerAction(cardPicked, *it, gameMap);
		}
		//cout << "after action" << endl;
		cardPicked.shift(icardPicked);
		if (ignoreValue == 0) {
			notify();
		}
		

		*startIndex = *startIndex + 1;
		count++;
		if (/*count +*/ *startIndex % *numberOfPlayers == 0) {
			it = (*players).begin();
		}
		else {
			std::advance(it, 1);
		}

	}

}

void Game::convertPlayerAction(Cards card, Player player, Map gameMap)
{//hardcode everything here before sending the region to the method lol
	int rValue = 0;
	//Region* reg;
	bool validAction = false;
	std::string s = card.singleAction.getAction();
	int totalActionAmount = card.singleAction.amount;
	//cout << "in action" << endl;
	/*std::string response;
	std::cout << "Do you want to ignore this action? (Y/N)" << endl;
	std::cin >> response;*/

	/*if (response == "Y") {
		s = "Y";
	}*/

	if (s.at(0) == 'A') {
		//verify if picked region has a city or not
		//cout << "add" << endl;
		gameMap.display();
		while (!validAction) {
			rValue = player.choose_target_region("ADD", gameMap);

			for (std::list<Region>::iterator it = (*(gameMap.eightMinEmpMap)).begin(); it != (*(gameMap.eightMinEmpMap)).end(); ++it) {

				if (*(it->val) == rValue) {
					if ((*it).compareRegions((gameMap.getStartingRegion())) || (*it).numberOfCityPerPlayer[player.chosenColor] != 0) {
						//reg = new Region(*it);
						player.placeNewArmies(&(*it), &(card.singleAction.amount));
						validAction = true;
						break;
					}
				}
				else {
					validAction = false;
				}

			}
		}

	}
	else if (s.at(0) == 'M') {

		int numberOfArmiesMoved = 0;

		while (numberOfArmiesMoved != totalActionAmount) {
			int currentMoveNumber;
			int currentMoveRegionFrom;
			int currentMoveRegionTo;

			gameMap.display();
			player.displayArmies();
			

			currentMoveNumber = player.choose_number_army_move("MOVE");

			currentMoveRegionFrom = player.choose_target_region("MOVE", gameMap);

			//cout << "\n\nTo which region do you want to move your army?\nGive the region's ID.: ";
			//std::cin >> currentMoveRegionTo;

			currentMoveRegionTo = player.choose_destination_Region("MOVE");

			if (validateMoveArmies(gameMap, player, currentMoveRegionFrom, currentMoveRegionTo, currentMoveNumber)) {
				Region* regionFrom = gameMap.findRegion(currentMoveRegionFrom);
				Region* regionTo = gameMap.findRegion(currentMoveRegionTo);
				player.moveArmies(regionFrom, regionTo, &currentMoveNumber);
				numberOfArmiesMoved += currentMoveNumber;
				std::cout << "move action completed. " << (totalActionAmount - numberOfArmiesMoved) << " armie(s) remain to move!" << std::endl;
			}
			else {
				std::cout << "You can not complete move action with the information you entered, try again!" << std::endl;
			}

		}
	}
	else if (s.at(0) == 'S') {
		//player.moveOverLand();
		int numberOfArmiesMoved = 0;

		while (numberOfArmiesMoved != totalActionAmount) {
			int currentMoveNumber;
			int currentMoveRegionFrom;
			int currentMoveRegionTo;

			gameMap.display();
			player.displayArmies();
			//cout << "\n\nEnter the number of armies you want to move: ";
			//std::cin >> currentMoveNumber;

			currentMoveNumber = player.choose_number_army_move("SHIP");

			currentMoveRegionFrom = player.choose_target_region("SHIP", gameMap);

			//cout << "\n\nTo which region do you want to move your army?\nGive the region's ID.: ";
			//std::cin >> currentMoveRegionTo;

			currentMoveRegionTo = player.choose_destination_Region("SHIP");

			if (validateMoveArmies2(gameMap, player, currentMoveRegionFrom, currentMoveRegionTo, currentMoveNumber)) {
				Region* regionFrom = gameMap.findRegion(currentMoveRegionFrom);
				Region* regionTo = gameMap.findRegion(currentMoveRegionTo);
				player.moveOverLand(regionFrom, regionTo, &currentMoveNumber);
				numberOfArmiesMoved += currentMoveNumber;
				std::cout << "move action completed. " << (totalActionAmount - numberOfArmiesMoved) << " armie(s) remain to move!" << std::endl;
			}
			else {
				std::cout << "You can not complete move action with the information you entered, try again!" << std::endl;
			}

		}

	}
	else if (s.at(0) == 'B') {
		//player.buildCity();

		if (player.discs != 0) {
			//while (!validAction) {
			gameMap.display();
			while (!validAction) {
				//cout << "\n\nIn which region do you want to build a city?\nGive the region's ID.";
				//std::cin >> rValue;
				rValue = player.choose_target_region("BUILD", gameMap);

				for (std::list<Region>::iterator it = (*(gameMap.eightMinEmpMap)).begin(); it != (*(gameMap.eightMinEmpMap)).end(); ++it) {

					if (*(it->val) == rValue) {
						if (!((*it).compareRegions((gameMap.getStartingRegion()))) && (*it).numberOfCityPerPlayer[player.chosenColor] == 0) {
							//reg = new Region(*it);
							player.buildCity(&(*it));
							validAction = true;
							break;
						}
					}
					else {
						validAction = false;
					}

				}
			}
			//}
		}
		else {
			cout << "You already built 3 cities.";
		}
	}
	else if (s.at(0) == 'D') {
		//player.destroyArmy();

		//while (!validAction) {
		int playerID = 0;
		Player* pChosen = new Player();
		gameMap.display();
		while (!validAction) {

			/*cout << "\n\nFor which player do you want to destroy an army?\nGive the Player's ID.";
			std::cin >> playerID;*/
			do {
				playerID = player.choose_playerID();
			} while (playerID <1 || playerID > *numberOfPlayers);
			int count = 0;
			for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {
				count++;
				if (count == playerID) {
					//pChosen = new Player(count, *((*it).tokenCoins), *((*it).playerAge), (*it).chosenColor);
					// TODO get le compteur et  chosenPlayerToDestroyArmy doit pointer vers le joueur pour lequel on veut détruire l'armée
					chosenPlayerToDestroyArmy = &(*it);
					break;
				}

			}
			//cout << "\n\nIn which region do you want to destroy an army?\nGive the region's ID.";
			//std::cin >> rValue;
			rValue = player.choose_target_region("DESTROY", gameMap);

			std::list<Player>::iterator p = (*players).begin();
			std::advance(p, count-1);
			for (std::list<Region>::iterator it = (*(gameMap.eightMinEmpMap)).begin(); it != (*(gameMap.eightMinEmpMap)).end(); ++it) {

				if (*(it->val) == rValue) {
					if ((*it).numberOfArmiesPerPlayer[p->chosenColor] != 0) {
						//reg = new Region(*it);

						// TODO modifier par le jouer pour lequel on veut détruire l'armée
						(*p).destroyArmy(&(*it), &(card.singleAction.amount));
						validAction = true;
						break;
					}
				}
				else {
					validAction = false;
				}

			}
		}
		//}
	
	}
	else {
		cout << "Action ignored.";
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
bool Game::validateMoveArmies(Map m, Player p, int regionFromVal, int regionToVal, int value)
{
	bool validMove = false;
	Region* regionFrom = m.findRegion(regionFromVal);
	if (regionFrom == nullptr) {
		std::cout << "\nRegion from which you want to move arnies does not exist" << std::endl;
		validMove = false;
	}
	else {

		// check player has enough armies to move
		if (regionFrom->numberOfArmiesPerPlayer[p.chosenColor] < value) {
			std::cout << "\nYou do not have enough armies in this region!" << std::endl;
			validMove = false;

		}
		else {
			// check neighbours
			bool neighbours = false;
			bool onSameContinent = true;
			for (std::list<Region>::iterator it = regionFrom->next->begin(); it != regionFrom->next->end(); ++it) {
				if (*(it->val) == regionToVal) {
					neighbours = true;
					if (*(regionFrom->continent) != *(it->continent)) {
						onSameContinent = false;
					}
					break;
				}
			}
			if (!neighbours) {
				std::cout << "\nRegions you entered are not meighbours" << std::endl;
				validMove = false;
			}
			else {
				if (onSameContinent) {
					validMove = true;
				}
				else {
					std::cout << "\nRegions you entered are not on the same continent" << std::endl;
					validMove = false;
				}
			}
		}

	}
	return validMove;
}
bool Game::validateMoveArmies2(Map m, Player p, int regionFromVal, int regionToVal, int value)
{
	bool validMove = false;
	Region* regionFrom = m.findRegion(regionFromVal);
	if (regionFrom == nullptr) {
		std::cout << "\nRegion from which you want to move arnies does not exist" << std::endl;
		validMove = false;
	}
	else {

		// check player has enough armies to move
		if (regionFrom->numberOfArmiesPerPlayer[p.chosenColor] < value) {
			std::cout << "\nYou do not have enough armies in this region!" << std::endl;
			validMove = false;

		}
		else {
			// check neighbours
			bool neighbours = false;
			bool onSameContinent = true;
			for (std::list<Region>::iterator it = regionFrom->next->begin(); it != regionFrom->next->end(); ++it) {
				if (*(it->val) == regionToVal) {
					neighbours = true;
					if (*(regionFrom->continent) != *(it->continent)) {
						onSameContinent = false;
					}
					break;
				}
			}
			if (!neighbours) {
				std::cout << "\nRegions you entered are not meighbours" << std::endl;
				validMove = false;
			}
			else {
				if (onSameContinent) {
					validMove = true;
				}
				else {
					//std::cout << "\nRegions you entered are not on the same continent" << std::endl;
					validMove = true;
				}
			}
		}

	}
	return validMove;
}
/*
void Game::compareScore(Map currentMap)
{
	nbRegions = currentMap.findNbRegions();
	int testCounter = 0;

	for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {
		it->findNbArmiesPerRegion(nbRegions);
	}

	//Determing player who owns a region
	for (int i = 0; i < nbRegions; i++) {
		int counter = 0; //counter represents player's ID
		int max = -1;
		bool hasSameNumberArmies = false;
		int sameNumberArmies = -1;

		for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {
			if (it->nbArmiesAndCitiesPerRegion.at(i) > max&& it->nbArmiesAndCitiesPerRegion.at(i) != 0) {
				regionControllers.at(i) = counter; //Player[counter] controls regions[i]
			}
			else if (it->nbArmiesAndCitiesPerRegion.at(i) == max) {
				//determines if there is a tie for the highest number of armies in a region
				hasSameNumberArmies = true;
				sameNumberArmies = it->nbArmiesAndCitiesPerRegion.at(i);
			}
			if (counter == *numberOfPlayers - 1 && max == sameNumberArmies && hasSameNumberArmies) {
				//removes region controllers on a tie
				regionControllers.at(i) = -1;
			}
			counter++;
		}
	}

	playersScore.resize(*numberOfPlayers, 0);
	playersCoins.resize(*numberOfPlayers, 0);
	playersArmies.resize(*numberOfPlayers, 0);
	nbRegionsOwn.resize(*numberOfPlayers, 0);

	//Storing each player's individual score
	int counter = 0;
	for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {
		//playersScore[counter] = it->computeScore(regionControllers, counter);
		playersScore.at(counter) = it->computeScore(regionControllers, counter);
		playersCoins.at(counter) = *(it->tokenCoins);
		playersArmies.at(counter) = *(it->totalNbArmies);
		nbRegionsOwn.at(counter) = *(it->nbControllingRegions);
		counter++;
	}

	int winner = -1;

	//Comparing players' scores
	int maxScore = 0;
	vector<int> possibleScoreWinners;

	for (int i = 0; i < *numberOfPlayers; i++) {
		if (playersScore[i] > maxScore) {
			possibleScoreWinners.resize(1, i);
			maxScore = playersScore[i];
		}
		else if (playersScore[i] == maxScore) {
			possibleScoreWinners.push_back(i);
		}
	}

	//Comparing players' coins
	int maxCoins = 0;
	vector<int> possibleCoinWinners;

	if (possibleScoreWinners.size() > 1) { //if there is a tie in scores
		for (int i = 0; i < possibleScoreWinners.size(); i++) {
			if (playersCoins.at(possibleScoreWinners.at(i)) > maxCoins) {
				possibleCoinWinners.resize(1, possibleScoreWinners.at(i));
				maxCoins = playersCoins.at(possibleScoreWinners.at(i));
			}
			else if (playersScore[i] == maxScore) {
				possibleCoinWinners.push_back(i);
			}
		}
	}
	else if (possibleScoreWinners.size() == 1) {
		winner = possibleScoreWinners.front();
	}

	//Comparing player's total number of armies
	int maxTotalNbArmies = 0;
	vector<int> possibleArmiesWinners;

	if (possibleCoinWinners.size() > 1) { //if there is still a tie in nb of coins
		for (int i = 0; i < possibleCoinWinners.size(); i++) {
			if (playersArmies.at(possibleCoinWinners.at(i)) > maxTotalNbArmies) {
				possibleArmiesWinners.resize(1, possibleCoinWinners.at(i));
				maxTotalNbArmies = playersArmies.at(possibleCoinWinners.at(i));
			}
			else if (playersScore[i] == maxScore) {
				possibleArmiesWinners.push_back(i);
			}
		}
	}
	else if (possibleCoinWinners.size() == 1) {
		winner = possibleCoinWinners.front();
	}

	//Comparing player's number of controlled regions
	int maxControlledRegions = 0;

	if (possibleArmiesWinners.size() > 1) { //if there is still a tie in nb of coins
		for (int i = 0; i < possibleArmiesWinners.size(); i++) {
			if (nbRegionsOwn.at(possibleArmiesWinners.at(i)) > maxControlledRegions) {
				winner = possibleArmiesWinners.at(i);
				maxControlledRegions = nbRegionsOwn.at(possibleArmiesWinners.at(i));
			}
		}
	}

	if (winner == -1) {
		cout << "Players have tied forever. There are no winners." << endl;
	}
	else {
		cout << "\nPlayer " << winner + 1 << " is the winner with " << playersScore.at(winner) << " points." << endl;
	}
}
*/

void Game::compareScore2(Map currentMap)
{
	nbRegions = currentMap.findNbRegions();

	for (std::list <Region>::const_iterator it = currentMap.eightMinEmpMap->begin(); it != currentMap.eightMinEmpMap->end(); ++it) {
		it->whoOwnRegion();
	}

	int testCounter = 0;

	//Determing player who owns a region
	for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {
		it->findNbArmiesPerRegion(nbRegions);
	}


	//playersScore.resize(*numberOfPlayers, 0);
	//playersCoins.resize(*numberOfPlayers, 0);
	//playersArmies.resize(*numberOfPlayers, 0);
	//nbRegionsOwn.resize(*numberOfPlayers, 0);

	//Computing each player's individual score and
	//Comparing players' scores
	int maxScore = 0;
	for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {
		//		playersScore.at(counter) = it->computeScore(currentMap);

		it->computeScore(currentMap);
		cout << "Game ~~~~~~~~  " << *(it->playerNumber) << " " <<
			" " << *(it->playerScore) << " " << *(it->tokenCoins) << endl;

		if (maxScore < *(it->playerScore)) {
			maxScore = *(it->playerScore);
		}
	}

	vector<Player*> possibleScoreWinners;

	int nb = 1;
	for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {
		if (maxScore == *(it->playerScore)) {
			//possibleScoreWinners.resize(nb++);
			possibleScoreWinners.push_back(&(*it));
		}
	}

	int winner = -1;

	if (possibleScoreWinners.size() == 1) {
		cout << "\nPlayer " << possibleScoreWinners.front()->chosenColor << " is the winner with " << *(possibleScoreWinners.front()->playerScore) << " points." << endl;
	}
	else {
		//Comparing players' coins
		int maxCoins = 0;
		vector<Player> possibleCoinWinners;

		for (std::vector<Player*>::iterator it = possibleScoreWinners.begin(); it != possibleScoreWinners.end(); ++it) {
			cout << "**************************   " << &(*it) << " " << *((*it)->tokenCoins) << " " << *((*it)->tokenCoins) << endl;
			if (maxCoins < *((*it)->tokenCoins)) {
				maxCoins = *((*it)->tokenCoins);
			}
		}
		nb = 1;
		for (std::vector<Player*>::iterator it = possibleScoreWinners.begin(); it != possibleScoreWinners.end(); ++it) {
			if (maxCoins == *((*it)->tokenCoins)) {
				//possibleCoinWinners.resize(nb++);
				possibleCoinWinners.push_back(*(*it));
			}
		}

		//Comparing player's total number of armies

		if (possibleCoinWinners.size() == 1) {
			cout << "\nPlayer " << possibleCoinWinners.front().chosenColor << " is the winner with " << *(possibleCoinWinners.front().playerScore) << " points." << endl;
		}
		else if (possibleCoinWinners.size() > 1) { //if there is still a tie in nb of coins
			int maxTotalNbArmies = 0;
			vector<Player> possibleArmiesWinners;
			for (std::vector<Player>::iterator it = possibleCoinWinners.begin(); it != possibleCoinWinners.end(); ++it) {
				if (maxTotalNbArmies < *(it->totalNbArmies)) {
					maxTotalNbArmies = *(it->totalNbArmies);
				}
			}
			nb = 1;
			for (std::vector<Player>::iterator it = possibleCoinWinners.begin(); it != possibleCoinWinners.end(); ++it) {
				if (maxTotalNbArmies == *(it->totalNbArmies)) {
					//possibleArmiesWinners.resize(nb++);
					possibleArmiesWinners.push_back((*it));
				}
			}

			if (possibleArmiesWinners.size() == 1) {//if there is still a tie in nb of coins
				cout << "\nPlayer " << possibleArmiesWinners.front().chosenColor << " is the winner with " << *(possibleArmiesWinners.front().playerScore) << " points." << endl;
			}
			else if (possibleArmiesWinners.size() > 1) {
				//Comparing player's number of controlled regions
				int maxControlledRegions = 0;
				vector<Player> possibleControlledRegionsWinners;

				for (std::vector<Player>::iterator it = possibleArmiesWinners.begin(); it != possibleArmiesWinners.end(); ++it) {
					if (maxControlledRegions < *(it->nbControllingRegions)) {
						maxControlledRegions = *(it->nbControllingRegions);
					}
				}
				nb = 1;
				for (std::vector<Player>::iterator it = possibleArmiesWinners.begin(); it != possibleArmiesWinners.end(); ++it) {
					if (maxControlledRegions == *(it->nbControllingRegions)) {
						//possibleControlledRegionsWinners.resize(nb++);
						possibleControlledRegionsWinners.push_back((*it));
					}
				}

				if (possibleControlledRegionsWinners.size() == 1) {
					cout << "\nPlayer " << possibleControlledRegionsWinners.front().chosenColor << " is the winner with " << *(possibleControlledRegionsWinners.front().playerScore) << " points." << endl;
				}
				else {
					cout << "Players have tied forever. There are no winners." << endl;
				}
			}

		}

	}

}


void Game::setView(ObserverView* v)
{
	view = v;
}

void Game::notify() {
	view->update();
}
