#include "Cards.h"
#include "Cardsfactory.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "Utility.h"

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

string SingleAction::getAction() {

	return action;

}

DoubleAction::DoubleAction() {
	firstAction = SingleAction("ADD", 2);
	secondAction = SingleAction("MOVE", 3);
}

DoubleAction::DoubleAction(SingleAction actionOne, SingleAction actionTwo) {
	firstAction = actionOne;
	secondAction = actionTwo;
}

SingleAction DoubleAction::getFirstAction() {
	return firstAction;
}

void DoubleAction::display() {
	firstAction.display();
	cout << "or" << endl;
	secondAction.display();
}

Cards::Cards() {
	singleAction = SingleAction();
	secondSingleAction = SingleAction();
	isTaken = false;
	isDoubleActionCard = false;
}

Cards::Cards(SingleAction aSingleAction, string aGood) {
	singleAction = aSingleAction;
	good = aGood;
	isTaken = false;
	isDoubleActionCard = false;
}

Cards::Cards(SingleAction first, SingleAction second, string aGood, string operation) {
	//doubleAction: aDoubleAction;
	singleAction = first;
	secondSingleAction = second;
	good = aGood;
	isTaken = false;
	isDoubleActionCard = true;
	actionsOperator = operation;
}

DoubleAction Cards::getDoubleAction() {
	return doubleAction;
}

int* Cards::initializeDeck()
{
	Cardsfactory* cardsfactory = Cardsfactory::getInstance();

	//FOREST
	fullDeck[0] = *(cardsfactory->createCard("MOVE", 3, "FOREST"));
	fullDeck[1] = *(cardsfactory->createCard("ADD", 3, "FOREST"));
	fullDeck[2] = *(cardsfactory->createCard("MOVE", 6, "FOREST"));
	//fullDeck[3] = *(cardsfactory->createCard("DESTROY", 1, "FOREST"));
	fullDeck[3] = *(cardsfactory->createCard("DESTROY", 1, "BUILD", 1, "FOREST", "OR"));
	fullDeck[4] = *(cardsfactory->createCard("ADD", 3, "FOREST"));
	fullDeck[5] = *(cardsfactory->createCard("SHIP", 4, "FOREST"));
	fullDeck[6] = *(cardsfactory->createCard("BUILD", 1, "FOREST"));
	fullDeck[7] = *(cardsfactory->createCard("SHIP", 3, "FOREST"));

	//CARROT
	fullDeck[8] = *(cardsfactory->createCard("BUILD", 1, "CARROT"));
	//fullDeck[9] = *(cardsfactory->createCard("DESTROY", 1, "CARROT"));
	fullDeck[9] = *(cardsfactory->createCard("DESTROY", 1, "ADD", 1, "CARROT", "AND"));
	fullDeck[10] = *(cardsfactory->createCard("ADD", 3, "CARROT"));
	fullDeck[11] = *(cardsfactory->createCard("MOVE", 4, "CARROT"));
	fullDeck[12] = *(cardsfactory->createCard("MOVE", 5, "CARROT"));
	fullDeck[13] = *(cardsfactory->createCard("ADD", 3, "CARROT"));
	fullDeck[14] = *(cardsfactory->createCard("SHIP", 3, "CARROT"));
	fullDeck[15] = *(cardsfactory->createCard("ADD", 4, "MOVE", 2, "CARROT", "OR"));
	fullDeck[16] = *(cardsfactory->createCard("MOVE", 4, "CARROT"));
	fullDeck[17] = *(cardsfactory->createCard("BUILD", 1, "CARROT"));

	//ANVIL
	fullDeck[18] = *(cardsfactory->createCard("MOVE", 4, "ANVIL"));
	//fullDeck[19] = *(cardsfactory->createCard("ADD", 3, "ANVIL"));
	fullDeck[19] = *(cardsfactory->createCard("ADD", 3, "MOVE", 4, "ANVIL", "OR"));
	fullDeck[20] = *(cardsfactory->createCard("MOVE", 5, "ANVIL"));
	fullDeck[21] = *(cardsfactory->createCard("ADD", 3, "ANVIL"));
	fullDeck[22] = *(cardsfactory->createCard("ADD", 3, "ANVIL"));
	fullDeck[23] = *(cardsfactory->createCard("SHIP", 3, "ANVIL"));
	fullDeck[24] = *(cardsfactory->createCard("BUILD", 1, "ANVIL"));
	fullDeck[25] = *(cardsfactory->createCard("MOVE", 4, "ANVIL"));
	fullDeck[26] = *(cardsfactory->createCard("ADD", 3, "MOVE", 3, "ANVIL", "OR"));

	//ORE
	fullDeck[27] = *(cardsfactory->createCard("MOVE", 2, "ORE"));
	fullDeck[28] = *(cardsfactory->createCard("SHIP", 3, "ORE"));
	fullDeck[29] = *(cardsfactory->createCard("SHIP", 2, "ORE"));
	fullDeck[30] = *(cardsfactory->createCard("MOVE", 2, "ORE"));
	fullDeck[31] = *(cardsfactory->createCard("ADD", 3, "ORE"));
	fullDeck[32] = *(cardsfactory->createCard("ADD", 3, "ORE"));
	fullDeck[33] = *(cardsfactory->createCard("ADD", 2, "ORE"));

	//CRYSTAL
	fullDeck[34] = *(cardsfactory->createCard("ADD", 2, "CRYSTAL"));
	fullDeck[35] = *(cardsfactory->createCard("ADD", 2, "CRYSTAL"));
	fullDeck[36] = *(cardsfactory->createCard("MOVE", 2, "CRYSTAL"));
	fullDeck[37] = *(cardsfactory->createCard("ADD", 1, "CRYSTAL"));
	fullDeck[38] = *(cardsfactory->createCard("ADD", 2, "CRYSTAL"));

	//WILD
	fullDeck[39] = *(cardsfactory->createCard("MOVE", 2, "WILD"));;
	fullDeck[40] = *(cardsfactory->createCard("MOVE", 2, "WILD"));;
	fullDeck[41] = *(cardsfactory->createCard("ADD", 2, "WILD"));;

	return nullptr;
}

int* Cards::shuffleCards()
{
	random_shuffle(std::begin(fullDeck), std::end(fullDeck));
	return nullptr;
}

void Cards::draw(int index)
{
	//draw card from fullDeck at specific index
	hand[index] = fullDeck[firstAvailableCard];
	fullDeck[firstAvailableCard].isTaken = true;
	firstAvailableCard += 1;

	//return nullptr;
}

Cards Cards::exchange(int cardIndex, bool isTournament)
{

	Cards* selectedCard = &hand[cardIndex];

	if (hand[cardIndex].isDoubleActionCard) {
		int actionChoice;
		cout << "\nYour card is a double action card."
			<< "\nWould you like to play the first(1) or the second(2) action?"
			<< "\nAction: ";
		if (isTournament) {
			actionChoice = 1;
		}
		else {
			inputHandling(&actionChoice, 1, 2);
		}

		if (actionChoice == 1) {
			*selectedCard = Cards(SingleAction(hand[cardIndex].singleAction.action, hand[cardIndex].singleAction.amount), hand[cardIndex].good);
		}
		else {
			*selectedCard = Cards(SingleAction(hand[cardIndex].secondSingleAction.action, hand[cardIndex].secondSingleAction.amount), hand[cardIndex].good);
		}
	}

	return *selectedCard;
}

void Cards::shift(int cardIndex) {

	for (int i = cardIndex; i < 5; i++) {
		hand[i] = hand[i + 1];
	}

	draw(5);

	displayFullHand();

}

void Cards::displayFullHand() {
	cout << "\n\nHand is now: \n" << endl;
	for (int i = 0; i < 6; i++) {
		displayHand(i);
	}

	std::cout << "\n\n";
}


void Cards::displayHand(int cardIndex)
{
	cout << "CARD " << cardIndex + 1 << ": " << cardsCost[cardIndex] << " COIN(S)" << endl;
	if (hand[cardIndex].isDoubleActionCard) {
		hand[cardIndex].singleAction.display();
		cout << "OR" << endl;
		hand[cardIndex].secondSingleAction.display();
	}
	else {
		hand[cardIndex].singleAction.display();
	}
	cout << "(" << hand[cardIndex].good << ")\n" << endl;
}

void Cards::displayCardAction()
{
	//cout << "CARD " << cardIndex + 1 << ": " << cardsCost[cardIndex] << " COIN(S)" << endl;
	(*this).singleAction.display();
	//cout << "(" << hand[cardIndex].good << ")\n" << endl;
}


int main5() {
	/*
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
	*/
	return 0;

}