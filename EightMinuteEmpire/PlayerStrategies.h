#pragma once
#include "Cards.h"
#include "Map.h"
//#include "Game.h"

class PlayerStrategies
{
public:
	int playerNumber;
	PlayerStrategies(int);
	virtual int chooseCard() const = 0;
	virtual int chooseTargetRegion(string action, Map m, int numberOfArmiesToMove) const = 0;
	virtual int chooseToIgnoreAction(string action) const = 0;
	virtual int chooseDestinationRegion(string action, Map m, int fromRegion) const = 0;
	virtual int choosePlayerToDestroyArmy(int numberOfPlayers) const = 0;
	virtual int chooseNumberOfArmyToMove(int numberOfArmiesLeftToMove) const = 0;
};

class InteractiveHuman : public PlayerStrategies
{
public:
	InteractiveHuman(int);
	virtual int chooseCard() const ;
	virtual int chooseTargetRegion(string action, Map m, int numberOfArmiesToMove) const;
	virtual int chooseToIgnoreAction(string action) const;
	virtual int chooseDestinationRegion(string action, Map m, int fromRegion) const;
	virtual int choosePlayerToDestroyArmy(int numberOfPlayers) const;
	virtual int chooseNumberOfArmyToMove(int numberOfArmiesLeftToMove) const;
};

class GreedyBot : public PlayerStrategies
{
public:
	GreedyBot(int);
	virtual int chooseCard() const ;
	virtual int chooseTargetRegion(string action, Map m, int numberOfArmiesToMove) const;
	virtual int chooseToIgnoreAction(string action) const;
	virtual int chooseDestinationRegion(string action, Map m, int fromRegion) const;
	virtual int choosePlayerToDestroyArmy(int numberOfPlayers) const;
	virtual int chooseNumberOfArmyToMove(int numberOfArmiesLeftToMove) const;
};

class ModerateBot : public PlayerStrategies
{
public:
	ModerateBot(int np);
	virtual int chooseCard() const ;
	virtual int chooseTargetRegion(string action, Map m, int numberOfArmiesToMove) const;
	virtual int chooseToIgnoreAction(string action) const;
	virtual int chooseDestinationRegion(string action, Map m, int fromRegion) const;
	virtual int choosePlayerToDestroyArmy(int numberOfPlayers) const;
	virtual int chooseNumberOfArmyToMove(int numberOfArmiesLeftToMove) const;
};

