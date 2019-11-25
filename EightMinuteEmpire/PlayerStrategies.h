#pragma once
#include "Cards.h"
#include "Map.h"

class PlayerStrategies
{
public:
	virtual int chooseCard() const = 0;
	virtual int chooseTargetRegion(string action, Map m) const = 0;
	//virtual int chooseDestinationRegion() const = 0;
	//virtual int choosePlayerToDestroyArmy() const = 0;
	//virtual int chooseNumberOfArmyToMove() const = 0;
};

class InteractiveHuman : public PlayerStrategies
{
public:
	virtual int chooseCard() const ;
	virtual int chooseTargetRegion(string action, Map m) const;
	//virtual int chooseDestinationRegion() ;
	//virtual int choosePlayerToDestroyArmy();
	//virtual int chooseNumberOfArmyToMove() ;
};

class GreedyBot : public PlayerStrategies
{
public:
	virtual int chooseCard() const ;
};

class ModerateBot : public PlayerStrategies
{
public:
	virtual int chooseCard() const ;
};

