#ifndef OV_H
#define OV_H

//add decls here 


#include "Game.h"
#include <list>
#include <string>
#include <vector>

class ObserverView {
	class Game* model;
public:
	ObserverView(Game* mod, int div);
	void update();
	Game* getGame();
	int mostCommon(vector<int> regionControllers);
};

#endif