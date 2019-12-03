#ifndef ML_H
#define ML_H

#include "Player.h"
#include <list>
#include <fstream>

using namespace std;

class MapLoader
{

public:


	ifstream inFile;
	Map* map;

	Map* readFile(string fileName);
	string readFolder(string fileName);
	void mapLoader();

};

#endif
