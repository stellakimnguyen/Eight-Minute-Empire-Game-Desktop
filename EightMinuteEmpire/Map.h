#pragma once

//graph
class Map
{
	/*
		Region* getAdjListNode(int dest, Region* head)
		{

			Region* newNode = new Region;
			newNode->val = dest;

			newNode->next = head;

			return newNode;
		}
	*/

public:

	Region** head;

};

//node
class Region // or country
{

public:

	int* continent;
	int* val; // id of the region
	Region* next; // adjacency - edges ( can point to more than one other region? )
	int* owner[]; //should be an array or not?
	int* readPlayerArmy();

};