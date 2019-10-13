#include <iostream>
#include "Cards.h"
#include "DriverCards.h"

using namespace std;

int * DriverCards::driverCardsTest()
{
	//CARDS
	Cards testing;
	testing.initializeDeck();
	Cards arrayTest[42];

	for (int i = 0; i < 42; i++) {
		arrayTest[i] = fullDeck[i];
	}

	testing.shuffleCards();

	std::cout << arrayTest[2].singleAction.amount;
	std::cout << fullDeck[2].singleAction.amount;

	return 0;
	return 0;
}
