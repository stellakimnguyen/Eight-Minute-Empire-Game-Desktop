#pragma once
#include "Cards.h"
#include "Map.h"

class PlayerStrategies
{
public:
	virtual int chooseCard() const = 0;
	virtual int chooseTargetRegion(string action, Map m) const = 0;
	virtual int chooseToIgnoreAction(string action) const = 0;
	virtual int chooseDestinationRegion(string action) const = 0;
	virtual int choosePlayerToDestroyArmy() const = 0;
	virtual int chooseNumberOfArmyToMove(string action) const = 0;
};

class InteractiveHuman : public PlayerStrategies
{
public:
	virtual int chooseCard() const ;
	virtual int chooseTargetRegion(string action, Map m) const;
	virtual int chooseToIgnoreAction(string action) const;
	virtual int chooseDestinationRegion(string action) const;
	virtual int choosePlayerToDestroyArmy() const;
	virtual int chooseNumberOfArmyToMove(string action) const;
};

class GreedyBot : public PlayerStrategies
{
public:
	virtual int chooseCard() const ;
	virtual int chooseTargetRegion(string action, Map m) const;
	virtual int chooseToIgnoreAction(string action) const;
};

class ModerateBot : public PlayerStrategies
{
public:
	virtual int chooseCard() const ;
	virtual int chooseTargetRegion(string action, Map m) const;
	virtual int chooseToIgnoreAction(string action) const;
};

