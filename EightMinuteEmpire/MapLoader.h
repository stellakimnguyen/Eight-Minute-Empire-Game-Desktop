
#include "Player.h"
#include <list>
#include <fstream>

using namespace std;

class MapLoader
{

public:


	ifstream inFile;
	Map* map;

	Map readFile(string fileName);
	void mapLoader();

};

