#include "Cardsfactory.h"

MoveAction::MoveAction(int anAmount) : SingleAction("MOVE", anAmount)
{
}

BuildAction::BuildAction(int anAmount) : SingleAction("BUILD", anAmount)
{
}

AddAction::AddAction(int anAmount) : SingleAction("ADD", anAmount)
{
}

DestroyAction::DestroyAction(int anAmount) : SingleAction("DESTROY", anAmount)
{
}

ShipAction::ShipAction(int anAmount) : SingleAction("SHIP", anAmount)
{
}

Cards* Cardsfactory::createCard(string type, int anAmount, string aGood)
{
	Cardsfactory* cardsfactory = Cardsfactory::getInstance();
	Cards* card = new Cards(*(cardsfactory->createSingleAction(type, anAmount)), aGood);
	return card;
}

Cards * Cardsfactory::createCard(string firstType, int firstAmount,
	string secondType, int secondAmount, string aGood, string operation)
{
	Cardsfactory* cardsFactory = Cardsfactory::getInstance();
	Cards* card = new Cards(*(cardsFactory->createSingleAction(firstType, firstAmount)), //first action
		*(cardsFactory->createSingleAction(secondType, secondAmount)), aGood, operation); //second action
	return card;
}

SingleAction* Cardsfactory::createSingleAction(string type, int anAmount) {
	if (type.compare("MOVE"))
		return new MoveAction(anAmount);
	else if (type.compare("ADD"))
		return new AddAction(anAmount);
	else if (type.compare("BUILD"))
		return new BuildAction(anAmount);
	else if (type.compare("DESTROY"))
		return new DestroyAction(anAmount);
	else if (type.compare("SHIP"))
		return new ShipAction(anAmount);
	else return NULL;
}

Cardsfactory* Cardsfactory::getInstance()
{
	static Cardsfactory mapInstance;
	return &mapInstance;
}

