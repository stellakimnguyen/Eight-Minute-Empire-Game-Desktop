#include "Player.h"
#include "Cards.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//CONSTRUCTORS
SingleAction::SingleAction() {
	action = "ADD";
	amount = 3;
}

SingleAction::SingleAction(string anAction, int anAmount) {
	action = anAction;
	amount = anAmount;
}

void SingleAction::display()
{
	std::cout << "Action:  " << action << ", " << "Amount:  " << amount << endl;
}

DoubleAction::DoubleAction() {
	firstAction = SingleAction("ADD", 2);
	secondAction = SingleAction("MOVE", 3);
}

DoubleAction::DoubleAction(SingleAction actionOne, SingleAction actionTwo) {
	firstAction = actionOne;
	secondAction = actionTwo;
}

void DoubleAction::display() {
	firstAction.display();
	cout << "or" << endl;
	secondAction.display();
}

Cards::Cards() {
	singleAction = SingleAction();
	doubleAction = DoubleAction();
	isTaken = false;
}

Cards::Cards(SingleAction aSingleAction, string aGood) {
	singleAction = aSingleAction;
	good = aGood;
	isTaken = false;
}

Cards::Cards(DoubleAction aDoubleAction, string aGood) {
	doubleAction: aDoubleAction;
	good: aGood;
	isTaken: false;
}

int* Cards::initializeDeck()
{
	//FOREST
	fullDeck[0] = Cards(SingleAction("MOVE", 3), "FOREST");
	fullDeck[1] = Cards(SingleAction(), "FOREST");
	fullDeck[2] = Cards(SingleAction("MOVE", 6), "FOREST");
	//fullDeck[3] = Cards(DoubleAction(SingleAction("DESTROY", 1), SingleAction("BUILD", 1)), "FOREST");
	fullDeck[3] = Cards(SingleAction("DESTROY", 1), "FOREST");
	//fullDeck[4] = Cards(DoubleAction(), "FOREST");
	fullDeck[4] = Cards(SingleAction(), "FOREST");
	fullDeck[5] = Cards(SingleAction("SHIP", 4), "FOREST");
	fullDeck[6] = Cards(SingleAction("BUILD", 1), "FOREST");
	fullDeck[7] = Cards(SingleAction("SHIP", 3), "FOREST");

	//CARROT
	fullDeck[8] = Cards(SingleAction("BUILD", 1), "CARROT");
	//fullDeck[9] = Cards(DoubleAction(SingleAction("DESTROY", 1), SingleAction("ADD", 1)), "CARROT");
	fullDeck[9] = Cards(SingleAction("DESTROY", 1), "CARROT");
	fullDeck[10] = Cards(SingleAction(), "CARROT");
	fullDeck[11] = Cards(SingleAction("MOVE", 4), "CARROT");
	fullDeck[12] = Cards(SingleAction("MOVE", 5), "CARROT");
	fullDeck[13] = Cards(SingleAction(), "CARROT");
	fullDeck[14] = Cards(SingleAction("SHIP", 3), "CARROT");
	//fullDeck[15] = Cards(DoubleAction(SingleAction("ADD", 4), SingleAction("MOVE", 2)), "CARROT");
	fullDeck[15] = Cards(SingleAction("ADD", 4), "CARROT");
	fullDeck[16] = Cards(SingleAction("MOVE", 4), "CARROT");
	fullDeck[17] = Cards(SingleAction("BUILD", 1), "CARROT");

	//ANVIL
	fullDeck[18] = Cards(SingleAction("MOVE", 4), "ANVIL");
	//fullDeck[19] = Cards(DoubleAction(SingleAction("ADD", 3), SingleAction("MOVE", 4)), "ANVIL");
	fullDeck[19] = Cards(SingleAction("ADD", 3), "ANVIL");
	fullDeck[20] = Cards(SingleAction("MOVE", 5), "ANVIL");
	fullDeck[21] = Cards(SingleAction("ADD", 3), "ANVIL");
	fullDeck[22] = Cards(SingleAction("ADD", 3), "ANVIL");
	fullDeck[23] = Cards(SingleAction("SHIP", 3), "ANVIL");
	fullDeck[24] = Cards(SingleAction("BUILD", 1), "ANVIL");
	fullDeck[25] = Cards(SingleAction("MOVE", 4), "ANVIL");
	//fullDeck[26] = Cards(DoubleAction(SingleAction("ADD", 3), SingleAction("MOVE", 3)), "ANVIL");
	fullDeck[26] = Cards(SingleAction("ADD", 3), "ANVIL");

	//ORE
	fullDeck[27] = Cards(SingleAction("MOVE", 2), "ORE");
	fullDeck[28] = Cards(SingleAction("SHIP", 3), "ORE");
	fullDeck[29] = Cards(SingleAction("SHIP", 2), "ORE");
	fullDeck[30] = Cards(SingleAction("MOVE", 2), "ORE");
	fullDeck[31] = Cards(SingleAction("ADD", 3), "ORE");
	fullDeck[32] = Cards(SingleAction("ADD", 3), "ORE");
	fullDeck[33] = Cards(SingleAction("ADD", 2), "ORE");

	//CRYSTAL
	fullDeck[34] = Cards(SingleAction("ADD", 2), "CRYSTAL");
	fullDeck[35] = Cards(SingleAction("ADD", 2), "CRYSTAL");
	fullDeck[36] = Cards(SingleAction("MOVE", 2), "CRYSTAL");
	fullDeck[37] = Cards(SingleAction("ADD", 1), "CRYSTAL");
	fullDeck[38] = Cards(SingleAction("ADD", 2), "CRYSTAL");

	//WILD
	fullDeck[39] = Cards(SingleAction("MOVE", 2), "WILD");
	fullDeck[40] = Cards(SingleAction("MOVE", 2), "WILD");
	fullDeck[41] = Cards(SingleAction("ADD", 2), "WILD");

	return nullptr;
}

int* Cards::shuffleCards()
{
	random_shuffle(std::begin(fullDeck), std::end(fullDeck));
	return nullptr;
}

int* Cards::draw(int index)
{
	//draw card from fullDeck at specific index
	hand[index] = fullDeck[firstAvailableCard];
	fullDeck[firstAvailableCard].isTaken = true;
	firstAvailableCard += 1;

	return nullptr;
}

int* Hand::exchange(Player currentPlayer, int cardIndex)
{
	//TO DO --------------------------------------------------------
	//substract Player's coins (playersCoins - cardsCost[cardIndex])
	//--------------------------------------------------------------

	//add hand[cardIndex] into Player own cards[]
	currentPlayer.takeCard(hand[cardIndex]);

	//shift (left) following cards to fill empty space
	std::rotate(begin(hand) + cardIndex, begin(hand) + cardIndex + 1, end(hand));
	//initialize exchangeCards[cardIndex] with draw()
	hand[5].draw(5);
	
	cout << "Hand is now: \n" << endl;
	for (int i = 0; i < 6; i++) {
		displayHand(i);
	}

	return nullptr;
}

void Hand::displayHand(int cardIndex)
{
	cout << "CARD " << cardIndex + 1 << ": " << cardsCost[cardIndex] << " COIN(S)" << endl;
	hand[cardIndex].singleAction.display();
	cout << "(" << hand[cardIndex].good << ")\n" << endl;
}


int main5() {
	Cards cardsTesting;
	Hand  handTesting;
	Player playerTesting = Player(1, 14, 23, Red);
	cardsTesting.initializeDeck(); //Create 42 cards
	cardsTesting.shuffleCards(); //Shuffle cards

	cout << "Hand: \n" << endl;
	for (int i = 0; i < 6; i++) {
		cardsTesting.draw(i); //drawing first 6 cards
		handTesting.displayHand(i); //displaying the hand
	}

	handTesting.exchange(playerTesting, 2);

	return 0;

}
