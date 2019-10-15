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

	testing.draw(6);

	//for (int i = 0; i < 6; ++i) {
	//	std::cout << "\n"; //toString from array of cards
	//}

	return 0;
	return 0;
}
