#include "Map.h"
#include <iostream>

using namespace std;

//int Region::readPlayerArmy()
//{
//	//read each player's number of stationary armies in the country if number > 0
//	return 0;
//}

bool Region::compareRegions(Region* reg)
{
	bool temp;

	temp = false;

	if ((continent == reg->continent) && (val == reg->val)) {
		temp = true;
	}
	
	return temp;
}

string Region::playerPath()
{
	string temp;

	cout << "Write the path for your next move. (to go from region 1 to 3 where 1 is adjacent to 2 that is adjacent to 3 you should write that your path is 123)";

	cin >> temp;

	return temp;
}

Region* Region::validateMove(Region* currentR, int* numberOfMoves, string s)
{

	bool isFound = false;
	Region* regionFound=nullptr;
	
	for (int i = 0; i < s.length(); i++)
	{
		isFound = false;
		for (std::list<Region>::iterator it = (*(it->next)).begin(); it != (*(it->next)).end(); ++it) {
			
			if (*((*it).cityNumber) == (int)(s.at(i))) {
				isFound = true;
				regionFound = new Region(*it);
				break;
			}

		}
		if (!isFound) {

			return nullptr;

		}
	}

	return regionFound;
}

void Region::whoOwnRegion() const
{
	int max = 0;

	for (int i = Red; i < White; i++)
	{
		if (max < numberOfArmiesPerPlayer.find((Colors)i)->second + numberOfCityPerPlayer.find((Colors)i)->second) {
			max = numberOfArmiesPerPlayer.find((Colors)i)->second + numberOfCityPerPlayer.find((Colors)i)->second;
			*regionOwner = i;
		}
	}
	// check if another player has the same number of armies and city
	for (int i = Red; i < White; i++)
	{
		if (max == numberOfArmiesPerPlayer.find((Colors)i)->second + numberOfCityPerPlayer.find((Colors)i)->second && *regionOwner != i) {
			*regionOwner = -1;
			break;
		}
	}
}

void Region::display() const
{
	if (*(startingRegion)) {
		cout << "*SR* ";
	}
	cout << "Region Id: " << *val << " continent Id: " << *continent << " neighbors: ";
	for (std::list<Region>::iterator it = next->begin(); it != next->end(); ++it) {
		//cout << *(it->val) << ", ";
		it->simple_display();
	}
	cout << endl;
	cout << "Region Id: " << *val << " Number of armies: " << *numberOfArmy << "  Number of cities : " << *cityNumber;
	cout << endl;
	cout << "[Armies] Red: " << numberOfArmiesPerPlayer.find(Red)->second << " Blue: " << numberOfArmiesPerPlayer.find(Blue)->second <<
		" Yellow: " << numberOfArmiesPerPlayer.find(Yellow)->second << " Green: " << numberOfArmiesPerPlayer.find(Green)->second <<
		" White: " << numberOfArmiesPerPlayer.find(White)->second;
	cout << endl;

	cout << "[Cities] Red: " << numberOfCityPerPlayer.find(Red)->second << " Blue: " << numberOfCityPerPlayer.find(Blue)->second <<
		" Yellow: " << numberOfCityPerPlayer.find(Yellow)->second << " Green: " << numberOfCityPerPlayer.find(Green)->second <<
		" White: " << numberOfCityPerPlayer.find(White)->second;
	cout << endl;
	cout << endl;

}

void Region::simple_display()
{
	cout << "(" << *val << ", " << *continent << ") ";
}

void Region::setStartingRegion(bool b)
{
	*startingRegion = b;
}

Region::Region(int v, int c)
{
	val = new int(v);
	continent = new int(c);
	numberOfArmy = new int(0);
	cityNumber = new int(0);
	regionOwner = new int(-1);
	next = new std::list <Region>();
	startingRegion = new bool(false);
	numberOfArmiesPerPlayer[Red] = 0;
	numberOfArmiesPerPlayer[Blue] = 0;
	numberOfArmiesPerPlayer[Yellow] = 0;
	numberOfArmiesPerPlayer[Green] = 0;
	numberOfArmiesPerPlayer[White] = 0;
	numberOfCityPerPlayer[Red] = 0;
	numberOfCityPerPlayer[Blue] = 0;
	numberOfCityPerPlayer[Yellow] = 0;
	numberOfCityPerPlayer[Green] = 0;
	numberOfCityPerPlayer[White] = 0;


}

Region::Region(const Region& region) //copy constructor
{

	val = region.val;
	continent = region.continent;
	numberOfArmy = region.numberOfArmy;
	cityNumber = region.cityNumber;
	next = region.next;
	startingRegion = region.startingRegion;
	regionOwner = region.regionOwner;
	numberOfArmiesPerPlayer[Red] = region.numberOfArmiesPerPlayer.find(Red)->second;
	numberOfArmiesPerPlayer[Blue] = region.numberOfArmiesPerPlayer.find(Blue)->second;
	numberOfArmiesPerPlayer[Yellow] = region.numberOfArmiesPerPlayer.find(Yellow)->second;
	numberOfArmiesPerPlayer[Green] = region.numberOfArmiesPerPlayer.find(Green)->second;
	numberOfArmiesPerPlayer[White] = region.numberOfArmiesPerPlayer.find(White)->second;

	numberOfCityPerPlayer[Red] = region.numberOfCityPerPlayer.find(Red)->second;
	numberOfCityPerPlayer[Blue] = region.numberOfCityPerPlayer.find(Blue)->second;
	numberOfCityPerPlayer[Yellow] = region.numberOfCityPerPlayer.find(Yellow)->second;
	numberOfCityPerPlayer[Green] = region.numberOfCityPerPlayer.find(Green)->second;
	numberOfCityPerPlayer[White] = region.numberOfCityPerPlayer.find(White)->second;

}


Region::~Region()
{
	delete val;
	delete continent;
	delete numberOfArmy;
	delete cityNumber;
	delete regionOwner;
	delete next;
	delete startingRegion;

	val = nullptr;
	continent = nullptr;
	numberOfArmy = nullptr;
	cityNumber = nullptr;
	regionOwner = nullptr;
	next = nullptr;
	startingRegion = nullptr;
}

Map Map::continentSubMap(int continent)
{
	Map m;
	for (std::list<Region>::iterator it = (*eightMinEmpMap).begin(); it != (*eightMinEmpMap).end(); ++it) {
		if (*(it->continent) == continent) {
			Region r(*(it->val), continent);
			for (std::list<Region>::iterator itNeigh = it->next->begin(); itNeigh != it->next->end(); ++itNeigh) {
				if (*(itNeigh->continent) == continent) {
					(r.next)->push_back(*itNeigh);
				}
			}
			(*(m.eightMinEmpMap)).push_back(r);
			// have to work neighbors
		}
	}

	return m;
}

bool Map::isConnected()
{
	std::list<Region> visited;
	for (std::list<Region>::iterator it = (*eightMinEmpMap).begin(); it != (*eightMinEmpMap).end(); ++it) {
		traverse(*it, visited);
		for (std::list<Region>::iterator itVis = visited.begin(); itVis != visited.end(); ++itVis) {
			cout << "visited " << *(itVis->val) << " "  << endl;
		}
		cout << *(it->val) << " " << visited.size() << endl;
		if (visited.size() != (*eightMinEmpMap).size()) {
			return false;
		}
	}
	return true;

}

void Map::traverse(Region u, std::list<Region>& visited) {
	bool inVisited = false;
	//check if viseted
	for (std::list<Region>::iterator itVis = visited.begin(); itVis != visited.end(); ++itVis) {
		if ((*(*itVis).val) == (*u.val)) {
			inVisited = true;
			break;
		}
	}
	if (!inVisited) {
		visited.push_back(u);
	}
	//all regions
	for (std::list<Region>::iterator it = (*eightMinEmpMap).begin(); it != (*eightMinEmpMap).end(); ++it) {
		//check if neighbor of u
		for (std::list<Region>::iterator itNeigh = (*u.next).begin(); itNeigh != (*u.next).end(); ++itNeigh) {
			if ((*(*it).val) == (*(*itNeigh).val)) {
				bool vis = false;
				//check if viseted
				for (std::list<Region>::iterator itVis = visited.begin(); itVis != visited.end(); ++itVis) {
					if ((*(*itVis).val) == (*(*itNeigh).val)) {
						vis = true;
						break;
					}
				}
				if (!vis) {
					traverse(*itNeigh, visited);
				}
				break;
			}
		}
	}
}

void Map::display()
{
	cout << "Regions in the map: " << endl;
	for (std::list<Region>::iterator it = eightMinEmpMap->begin(); it != eightMinEmpMap->end(); ++it) {
		it->display();
	}
	
	cout << endl;
}

void Map::setStartingRegion(Region* startingR)
{
	startingRegion = startingR;
}

Region* Map::getStartingRegion()
{
	return startingRegion;
}

void Map::addRegion(Region r)
{
	eightMinEmpMap->push_back(r);
}

int Map::findNbRegions()
{
	int count = 0;
	for (std::list<Region>::iterator it = (*eightMinEmpMap).begin(); it != (*eightMinEmpMap).end(); ++it) {
		count++;
	}

	return count;
}

Region* Map::findRegion(int val)
{
	for (std::list<Region>::iterator it = (*eightMinEmpMap).begin(); it != (*eightMinEmpMap).end(); ++it) {
		if (*(it->val) == val) {
			return &(*it);
		}
	}

	return nullptr;
}

Map* Map::getInstance()
{
	static Map mapInstance;

	return &mapInstance;
}

Map::Map()
{
	eightMinEmpMap = new std::list<Region>();
	//nbRegions = new int(0);
}

Map::~Map()
{
	delete eightMinEmpMap;
	eightMinEmpMap = nullptr;
}


bool Region::operator==(const Region& argument) const
{
	return val == argument.val;
}