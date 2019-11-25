#include "ObserverView.h"
#include <iostream>
#include <vector>


ObserverView::ObserverView(Game* mod, int div)
{
	model = mod;
}

void ObserverView::update()
{
	// 6. "Pull" information of interest
	cout << "ooooooooooooooooooooooooooooooooooooooooooooooo" << endl;
	int playerPos = *(getGame()->startIndex) % *(getGame()->numberOfPlayers) + 1;
	std::list<Player>::iterator it = getGame()->players->begin();
	std::advance(it, playerPos - 1);

	MoveDesc md = it->moveDesc->back();
	Cards c = it->cards->back();

	std::string s = c.singleAction.getAction();
	int totalActionAmount = c.singleAction.amount;
	cout << "Player " << playerPos << ": select ";
	it->cards->back().displayCardAction();
	cout << "Paid  " << cardsCost[*(getGame()->selectedCardIndex)] << " coins" << '\n';
	if (md.regionFrom != nullptr) {
		if (s.at(0) == 'A') {
			cout << "Player added " << totalActionAmount << " armies to region " << *(md.regionFrom->val) << endl;
		}
		else if (s.at(0) == 'M') {
			cout << "Player moved " << totalActionAmount << " armies from region " << *(md.regionFrom->val) << " to " << *(md.regionTo->val) << endl;
		}
		else if (s.at(0) == 'B') {
			cout << "Player built " << totalActionAmount << " city in region " << *(md.regionFrom->val) << endl;
		}
		else if (s.at(0) == 'D') {
			Player* p = getGame()->chosenPlayerToDestroyArmy;
			MoveDesc md = p->moveDesc->back();
			cout << "Player destroyed an army for player " << (p->chosenColor+1)  << " in region " << *(md.regionFrom->val) << endl;
		}
		cout << endl;
		int count = 1;
		for (std::list<Player>::iterator it = getGame()->players->begin(); it != getGame()->players->end(); ++it) {
			it->computeScore(*(getGame()->map));
			cout << "Player # " << count << " [" << getGame()->return_value(it->chosenColor) <<"] has a score of " << *(it->playerScore) << endl;
			cout << "He has armies/city in the following regions (# of armies, # of cities): ";
			for (std::list <Region>::const_iterator itReg = getGame()->map->eightMinEmpMap->begin(); itReg != getGame()->map->eightMinEmpMap->end(); ++itReg) {
				itReg->whoOwnRegion();
				if (itReg->numberOfArmiesPerPlayer.find((Colors)it->chosenColor)->second != 0 ||
					itReg->numberOfCityPerPlayer.find((Colors)it->chosenColor)->second != 0) {
					cout << *(itReg->val) << "(" << itReg->numberOfArmiesPerPlayer.find((Colors)it->chosenColor)->second
						<< ", " << itReg->numberOfCityPerPlayer.find((Colors)it->chosenColor)->second << "), ";
				}
			}
			cout << endl;
			//for (std::list <Region>::const_iterator itReg = it->regionOwned->begin(); itReg != it->regionOwned->end(); ++itReg) {
			//	itReg->display();
			//}

			count++;
		}

		cout << "\n-----------------------------------------------" << endl;

		vector< vector<int> > continentRegions;

		for (std::list <Region>::const_iterator itReg = getGame()->map->eightMinEmpMap->begin(); itReg != getGame()->map->eightMinEmpMap->end(); ++itReg) {
			itReg->whoOwnRegion();
			if (*(itReg->regionOwner) != -1) {
				cout << "Region " << *(itReg->val) << " is owned by Player #" << (*(itReg->regionOwner) +1) << endl;
			}

			if (*(itReg->continent) > continentRegions.size()) {
				continentRegions.resize(*(itReg->continent));
				continentRegions.at(*(itReg->continent) - 1).push_back(*(itReg->regionOwner));
			}
		}

		for (int i = 0; i < continentRegions.size(); i++) {
			int continentController = mostCommon(continentRegions.at(i));

			if (mostCommon(continentRegions.at(i)) != -1) {
				cout << "Continent " << i + 1 << " is owned by Player #" << continentController + 1 << endl;
			}
		}
	}
	else {
		cout << "action ignored" << endl;
	}
	cout << "ooooooooooooooooooooooooooooooooooooooooooooooo" << endl;

}

Game* ObserverView::getGame()
{
	return model;
}

int ObserverView::mostCommon(vector<int> regionControllers)
{
	int max = 0;
	int mostCommon = -1;
	map<int, int> m;
	for (std::vector<int>::iterator it = regionControllers.begin(); it != regionControllers.end(); it++) {
		m[*it]++;
		if (m[*it] > max) {
			max = m[*it];
			mostCommon = *it;
		}
	}

	return mostCommon;
}


