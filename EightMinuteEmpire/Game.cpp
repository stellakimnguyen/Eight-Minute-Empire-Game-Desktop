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

	myGame.gameLoop(gameMap);

	myGame.compareScore(gameMap);

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

	selectedCardIndex = new int(-1);
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
	cout << "TEST ---------------------------------------!!!!!" << endl;
	fullDeck[3].doubleAction.display();
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

		std::cout << "\nWhich card are you taking from the hand? " << endl;
		std::cin >> icardPicked;
		icardPicked--;

		*(selectedCardIndex) = icardPicked;

		cardPicked = cardPicked.exchange(icardPicked); //could be static?
		(*it).payCoin(&(cardsCost[icardPicked])); //player pays coins

		cardPicked.displayCardAction();//display
		cardPicked.isTaken = true;
		//add card to player cards
		(*it).takeCard(cardPicked); //DOES NOT WORK
		//cout << "before action" << endl;
		//do a case action -> call method in player with correct arguments
		//convertPlayerAction(cardPicked, *it, gameMap);
		//cout << "after action" << endl;
		cardPicked.shift(icardPicked);

		//notify();

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

//void Game::convertPlayerAction(Cards card, Player player, Map gameMap)
//{//hardcode everything here before sending the region to the method lol
//	int rValue = 0;
//	//Region* reg;
//	bool validAction = false;
//	//std::string s = card.singleAction.getAction();
//	int totalActionAmount = card.singleAction.amount;
//	//cout << "in action" << endl;
//	/*std::string response;
//	std::cout << "Do you want to ignore this action? (Y/N)" << endl;
//	std::cin >> response;*/
//
//	/*if (response == "Y") {
//		s = "Y";
//	}*/
//
//	if (s.at(0) == 'A') {
//		//verify if picked region has a city or not
//		//cout << "add" << endl;
//		gameMap.display();
//		while (!validAction) {
//			std::cout << "\n\nIn which region do you want to add soldiers?\nGive the region's ID.";
//			std::cin >> rValue;
//
//			for (std::list<Region>::iterator it = (*(gameMap.eightMinEmpMap)).begin(); it != (*(gameMap.eightMinEmpMap)).end(); ++it) {
//
//				if (*(it->val) == rValue) {
//					if ((*it).compareRegions((gameMap.getStartingRegion())) || (*it).numberOfCityPerPlayer[player.chosenColor] != 0) {
//						//reg = new Region(*it);
//						player.placeNewArmies(&(*it), &(card.singleAction.amount));
//						validAction = true;
//						break;
//					}
//				}
//				else {
//					validAction = false;
//				}
//
//			}
//		}
//
//	}
//	else if (s.at(0) == 'M') {
//
//		int numberOfArmiesMoved = 0;
//
//		while (numberOfArmiesMoved != totalActionAmount) {
//			int currentMoveNumber;
//			int currentMoveRegionFrom;
//			int currentMoveRegionTo;
//
//			gameMap.display();
//			player.displayArmies();
//			cout << "\n\nEnter the number of armies you want to move: ";
//			std::cin >> currentMoveNumber;
//
//			cout << "\n\nFrom which region do you want to move your army?\nGive the region's ID.: ";
//			std::cin >> currentMoveRegionFrom;
//
//			cout << "\n\nTo which region do you want to move your army?\nGive the region's ID.: ";
//			std::cin >> currentMoveRegionTo;
//
//			if (validateMoveArmies(gameMap, player, currentMoveRegionFrom, currentMoveRegionTo, currentMoveNumber)) {
//				Region* regionFrom = gameMap.findRegion(currentMoveRegionFrom);
//				Region* regionTo = gameMap.findRegion(currentMoveRegionTo);
//				player.moveArmies(regionFrom, regionTo, &currentMoveNumber);
//				numberOfArmiesMoved += currentMoveNumber;
//				std::cout << "move action completed. " << (totalActionAmount - numberOfArmiesMoved) << " armie(s) remain to move!" << std::endl;
//			}
//			else {
//				std::cout << "You can not complete move action with the information you entered, try again!" << std::endl;
//			}
//
//		}
//	}
//	else if (s.at(0) == 'S') {
//		//player.moveOverLand();
//
//		cout << "\n\nTo which region do you want to move your army?\nGive the region's ID.";
//		std::cin >> rValue;
//
//
//
//	}
//	else if (s.at(0) == 'B') {
//		//player.buildCity();
//
//		if (player.discs != 0) {
//			//while (!validAction) {
//			gameMap.display();
//			while (!validAction) {
//				cout << "\n\nIn which region do you want to build a city?\nGive the region's ID.";
//				std::cin >> rValue;
//
//				for (std::list<Region>::iterator it = (*(gameMap.eightMinEmpMap)).begin(); it != (*(gameMap.eightMinEmpMap)).end(); ++it) {
//
//					if (*(it->val) == rValue) {
//						if (!((*it).compareRegions((gameMap.getStartingRegion()))) && (*it).numberOfCityPerPlayer[player.chosenColor] == 0) {
//							//reg = new Region(*it);
//							player.buildCity(&(*it));
//							validAction = true;
//							break;
//						}
//					}
//					else {
//						validAction = false;
//					}
//
//				}
//			}
//			//}
//		}
//		else {
//			cout << "You already built 3 cities.";
//		}
//	}
//	else if (s.at(0) == 'D') {
//		//player.destroyArmy();
//
//		//while (!validAction) {
//		int playerID = 0;
//		Player* pChosen = new Player();
//		gameMap.display();
//		while (!validAction) {
//
//			cout << "\n\nFor which player do you want to destroy an army?\nGive the Player's ID.";
//			std::cin >> playerID;
//			int count = 0;
//			for (std::list<Player>::iterator it = (*players).begin(); it != (*players).end(); ++it) {
//
//				if (count == playerID) {
//					pChosen = new Player(count, *((*it).tokenCoins), *((*it).playerAge), (*it).chosenColor);
//					// TODO get le compteur et  chosenPlayerToDestroyArmy doit pointer vers le joueur pour lequel on veut détruire l'armée
//					chosenPlayerToDestroyArmy = &(*it);
//					break;
//				}
//
//			}
//			cout << "\n\nIn which region do you want to destroy an army?\nGive the region's ID.";
//			std::cin >> rValue;
//
//			std::list<Player>::iterator p = (*players).begin();
//			std::advance(p, count);
//			for (std::list<Region>::iterator it = (*(gameMap.eightMinEmpMap)).begin(); it != (*(gameMap.eightMinEmpMap)).end(); ++it) {
//
//				if (*(it->val) == rValue) {
//					if ((*it).numberOfArmiesPerPlayer[pChosen->chosenColor] != 0) {
//						//reg = new Region(*it);
//
//						// TODO modifier par le jouer pour lequel on veut détruire l'armée
//						(*p).destroyArmy(&(*it), &(card.singleAction.amount));
//						validAction = true;
//						break;
//					}
//				}
//				else {
//					validAction = false;
//				}
//
//			}
//		}
//		//}
//
//	}
//	else {
//		cout << "Action ignored.";
//	}
//
//}

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
			if (it->nbArmiesAndCitiesPerRegion.at(i) > max  && it->nbArmiesAndCitiesPerRegion.at(i) != 0) {
				regionControllers.at(i) = counter; //Player[counter] controls regions[i]
			} else if (it->nbArmiesAndCitiesPerRegion.at(i) == max) {
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