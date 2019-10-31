#include "Cards.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//CONSTRUCTORS
SingleAction::SingleAction() {
	action = "ADD";
	amount = 3;
	entity = "ARMIES";
	terrain = "LAND";
}
 
SingleAction::SingleAction(string anAction, int anAmount, string anEntity, string aTerrain) {
	action = anAction;
	amount = anAmount;
	entity = anEntity;
	terrain = aTerrain;
}

DoubleAction::DoubleAction() {
	firstAction = SingleAction("ADD", 2, "ARMIES", "LAND");
	secondAction = SingleAction("MOVE", 3, "ARMIES", "LAND");
}

DoubleAction::DoubleAction(SingleAction actionOne, SingleAction actionTwo) {
	firstAction = actionOne;
	secondAction = actionTwo;
}

Cards::Cards() {
	singleAction = SingleAction();
	doubleAction = DoubleAction();
	isTaken = false;
}

Cards::Cards(SingleAction aSingleAction, string aGood) {
	singleAction: aSingleAction;
	good: aGood;
	isTaken: false;
}

Cards::Cards(DoubleAction aDoubleAction, string aGood) {
	doubleAction: aDoubleAction;
	good: aGood;
	isTaken: false;
}

int* Cards::initializeDeck()
{
	////TEST
	//SingleAction ForestOne = SingleAction("MOVE", 3, "ARMIES", "LAND");
	//SingleAction ForestThree = SingleAction("MOVE", 6, "ARMIES", "WATER");
	//SingleAction ForestFour = SingleAction("MOVE", 1, "ARMIES", "WATER");
	//SingleAction ForestFive = SingleAction("MOVE", 7, "ARMIES", "LAND");

	//test[0] = Cards(ForestOne, "FOREST");
	//test[1] = Cards(SingleAction(), "FOREST");
	//test[2] = Cards(ForestThree, "FOREST");
	//test[3] = Cards(ForestFour, "FOREST");
	//test[4] = Cards(ForestFive, "FOREST");

	//std::cout << test[0].singleAction.amount;
	//std::cout << "\nInitial Array: ";

	/*for (int i = 0; i < 5; ++i) {
		std::cout << test[i].singleAction.amount << " ";
	}

	random_shuffle(std::begin(test), std::end(test));
	std::cout << "\nShuffled Array: ";
	
	for (int i = 0; i < 5; ++i) {
		testTest[i] = test[i];
		std::cout << testTest[i].singleAction.amount << " ";
	}*/


	//FOREST
	fullDeck[0] = Cards(SingleAction("MOVE", 3, "ARMIES", "LAND"), "FOREST");
	fullDeck[1] = Cards(SingleAction(), "FOREST");
	fullDeck[2] = Cards(SingleAction("MOVE", 6, "ARMIES", "LAND"), "FOREST");
	fullDeck[3] = Cards(DoubleAction(SingleAction("DESTROY", 1, "ARMIES", "LAND"), SingleAction("BUILD", 1, "CITY", "LAND")), "FOREST");
	fullDeck[4] = Cards(DoubleAction(), "FOREST");
	fullDeck[5] = Cards(SingleAction("MOVE", 4, "ARMIES", "WATER"), "FOREST");
	fullDeck[6] = Cards(SingleAction("BUILD", 1, "CITY", "LAND"), "FOREST");
	fullDeck[7] = Cards(SingleAction("MOVE", 3, "ARMIES", "WATER"), "FOREST");

	//CARROT
	fullDeck[8] = Cards(SingleAction("BUILD", 1, "CITY", "LAND"), "CARROT");
	fullDeck[9] = Cards(DoubleAction(SingleAction("DESTROY", 1, "ARMIES", "LAND"), SingleAction("ADD", 1, "ARMIES", "LAND")), "CARROT");
	fullDeck[10] = Cards(SingleAction(), "CARROT");
	fullDeck[11] = Cards(SingleAction("MOVE", 4, "ARMIES", "LAND"), "CARROT");
	fullDeck[12] = Cards(SingleAction("MOVE", 5, "ARMIES", "LAND"), "CARROT");
	fullDeck[13] = Cards(SingleAction(), "CARROT");
	fullDeck[14] = Cards(SingleAction("MOVE", 3, "ARMIES", "WATER"), "CARROT");
	fullDeck[15] = Cards(DoubleAction(SingleAction("ADD", 4, "ARMIES", "LAND"), SingleAction("MOVE", 2, "ARMIES", "LAND")), "CARROT");
	fullDeck[16] = Cards(SingleAction("MOVE", 4, "ARMIES", "LAND"), "CARROT");
	fullDeck[17] = Cards(SingleAction("BUILD", 1, "CITY", "LAND"), "CARROT");

	//ANVIL
	fullDeck[18] = Cards(SingleAction("MOVE", 4, "ARMIES", "LAND"), "ANVIL");
	fullDeck[19] = Cards(DoubleAction(SingleAction("ADD", 3, "ARMIES", "LAND"), SingleAction("MOVE", 4, "ARMIES", "LAND")), "ANVIL");
	fullDeck[20] = Cards(SingleAction("MOVE", 5, "ARMIES", "LAND"), "ANVIL");
	fullDeck[21] = Cards(SingleAction("ADD", 3, "ARMIES", "LAND"), "ANVIL");
	fullDeck[22] = Cards(SingleAction("ADD", 3, "ARMIES", "LAND"), "ANVIL");
	fullDeck[23] = Cards(SingleAction("MOVE", 3, "ARMIES", "WATER"), "ANVIL");
	fullDeck[24] = Cards(SingleAction("BUILD", 1, "CITY", "LAND"), "ANVIL");
	fullDeck[25] = Cards(SingleAction("MOVE", 4, "ARMIES", "LAND"), "ANVIL");
	fullDeck[26] = Cards(DoubleAction(SingleAction("ADD", 3, "ARMIES", "LAND"), SingleAction("MOVE", 3, "ARMIES", "LAND")), "ANVIL");

	//ORE
	fullDeck[27] = Cards(SingleAction("MOVE", 2, "ARMIES", "LAND"), "ORE");
	fullDeck[28] = Cards(SingleAction("MOVE", 3, "ARMIES", "WATER"), "ORE");
	fullDeck[29] = Cards(SingleAction("MOVE", 2, "ARMIES", "WATER"), "ORE");
	fullDeck[30] = Cards(SingleAction("MOVE", 2, "ARMIES", "WATER"), "ORE");
	fullDeck[31] = Cards(SingleAction("ADD", 3, "ARMIES", "LAND"), "ORE");
	fullDeck[32] = Cards(SingleAction("ADD", 3, "ARMIES", "LAND"), "ORE");
	fullDeck[33] = Cards(SingleAction("ADD", 2, "ARMIES", "LAND"), "ORE");

	//CRYSTAL
	fullDeck[34] = Cards(SingleAction("ADD", 2, "ARMIES", "LAND"), "CRYSTAL");
	fullDeck[35] = Cards(SingleAction("ADD", 2, "ARMIES", "LAND"), "CRYSTAL");
	fullDeck[36] = Cards(SingleAction("MOVE", 2, "ARMIES", "LAND"), "CRYSTAL");
	fullDeck[37] = Cards(SingleAction("ADD", 1, "ARMIES", "LAND"), "CRYSTAL");
	fullDeck[38] = Cards(SingleAction("ADD", 2, "ARMIES", "LAND"), "CRYSTAL");

	//WILD
	fullDeck[39] = Cards(SingleAction("MOVE", 2, "ARMIES", "LAND"), "WILD");
	fullDeck[40] = Cards(SingleAction("MOVE", 2, "ARMIES", "LAND"), "WILD");
	fullDeck[41] = Cards(SingleAction("ADD", 2, "ARMIES", "LAND"), "WILD");

	std::cout << fullDeck[5].singleAction.action;

	return nullptr;
}

int * Cards::shuffleCards()
{
	random_shuffle(std::begin(fullDeck), std::end(fullDeck));
	return nullptr;
}

int* Cards::draw(int cardsToDraw)
{
	shuffleCards();
	for (int i = 0; i < cardsToDraw; i++) {
		exchangeCards[i] = fullDeck[i];
		fullDeck[i].isTaken = true;
	}

	return nullptr;
}

int* Hand::exchange(int cardIndex)
{
	//take card at [cardIndex] from exchangeCards[]
	//empty exchangeCards[cardIndex]
	//intialize exchangeCards[cardIndex] with draw()
	//add card into Player object's attribute cards[]/hands[]
	return nullptr;
}
