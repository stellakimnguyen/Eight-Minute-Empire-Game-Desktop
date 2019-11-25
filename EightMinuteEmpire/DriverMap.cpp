//#include "DriverMap.h"
//#include "Map.h"
//#include <iostream>
//#include <list>
//
//using namespace std;
//
//
//void driverMapTest(){
//	Region* r1 = new Region(1, 1), * r2 = new Region(2, 1), * r3 = new Region(3, 1);
//	Region* r4 = new Region(4, 2), * r5 = new Region(5, 2), * r6 = new Region(6, 3);
//	r1->next->push_back(*r2);
//	r2->next->push_back(*r1);
//	r1->next->push_back(*r3);
//	r3->next->push_back(*r1);
//	r2->next->push_back(*r4);
//	r4->next->push_back(*r2);
//	r5->next->push_back(*r6);
//	r6->next->push_back(*r5);
//	r3->next->push_back(*r6);
//	r6->next->push_back(*r3);
//	Map* map = new Map();
//	map->eightMinEmpMap->push_back(*r1);
//	map->eightMinEmpMap->push_back(*r2);
//	map->eightMinEmpMap->push_back(*r3);
//	map->eightMinEmpMap->push_back(*r4);
//	map->eightMinEmpMap->push_back(*r5);
//	map->eightMinEmpMap->push_back(*r6);
//
//	cout << map->isConnected() << endl;
//
//	cout << "regions in subcontinent 1 " << endl;
//	Map c1 = map->continentSubMap(1);
//
//	for (std::list<Region>::iterator it = (c1.eightMinEmpMap)->begin(); it != (c1.eightMinEmpMap)->end(); ++it) {
//		cout << *(it->val) << "\n";
//	}
//	c1.display();
//	cout << "continent 1 is connected: " << c1.isConnected() << endl;
//	cout << "regions in subcontinent 2 " << endl;
//	Map c2 = map->continentSubMap(2);
//
//	for (std::list<Region>::iterator it = (c2.eightMinEmpMap)->begin(); it != (c2.eightMinEmpMap)->end(); ++it) {
//		cout << *(it->val) << "\n";
//	}
//	c2.display();
//	cout << "continent 2 is connected: " << c2.isConnected() << endl;
//
//}
