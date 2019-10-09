#pragma once
class Cards
{

public:

	int* value; // price of the card
	int* action;
	int* good;

	int* draw();
	int* initializingDeck(); // initializes hand

	// should we initialize the whole 42 cards at the beginning?


	//CTRL + K C   CTRL + K U
	class Carrot;
	class Forest;
	class Anvil;
	class Ore;
	class Crystal;
	class Wild;

};

class Hand //is hand what a player has in their hand or is it the row from which they pick?
{

public:


	int* cards[];
	int* exchange();

};


class Cards::Carrot : public Cards {

};

class Cards::Forest : public Cards {

};

class Cards::Anvil : public Cards {

};

class Cards::Ore : public Cards {

};

class Cards::Crystal : public Cards {

};

class Cards::Wild : public Cards {


};
