#pragma once
#include "cards.h"
#include <string>
#include <vector>
#include <iostream> 

using namespace std;


class MoveAction : public SingleAction {
public:
	MoveAction(int);
};

class DestroyAction : public SingleAction {
public:
	DestroyAction(int);
};

class ShipAction : public SingleAction {
public:
	ShipAction(int);
};

class AddAction : public SingleAction {
public:
	AddAction(int);
};

class BuildAction : public SingleAction {
public:
	BuildAction(int);
};


// Client class 
class Client {
public:

	Client();
	~Client();
	SingleAction* getAction();

private:
	SingleAction* pVehicle;
};

class Cardsfactory
{
	Cardsfactory() {
	}
public :
	Cards* createCard(string, int, string);
	SingleAction* createSingleAction(string, int);
	static Cardsfactory* getInstance();

};

