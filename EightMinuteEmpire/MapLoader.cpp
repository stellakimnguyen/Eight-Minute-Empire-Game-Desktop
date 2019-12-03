#include "MapLoader.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <iterator>
#include <vector>
#include <dirent.h>

int main4() {

	MapLoader* mapL = new MapLoader();

	mapL->readFile("test2.txt");

	return 0;

	delete mapL;
	mapL = nullptr;
}


Map* MapLoader::readFile(string fileName)
{

	inFile.open(fileName);
	if (!inFile) {
		cout << "Cannot open this file.";
		cout << "The program will now exit";
		exit(1);

	}

	string line;
	//std::list<Region>* regions = new std::list<Region>();
	std::map<std::string, std::string> regCont;

	Map* gameMap = Map::getInstance();
	Map* gameMap2 = Map::getInstance();

	std::cout << "gameMap " << gameMap << std::endl;
	std::cout << "gameMap2 " << gameMap2 << std::endl;

	int startingRegionVal = -1;
	if (getline(inFile, line)) {

		if (line.find(":") != std::string::npos) {
			std::cout << "first line in file should contain starting region val" << '\n';
		}
		else {


			startingRegionVal = std::stoi(line);
			while (getline(inFile, line)) {


				std::string s = line;
				std::string delimiter = ":";

				size_t pos = 0;
				std::string token1, token2, token3;

				int i = 0;
				Region r(-1, -1);
				//regions->push_back(r);
				gameMap->addRegion(r);
				while ((pos = s.find(delimiter)) != std::string::npos) {
					if (i == 0) {
						token1 = s.substr(0, pos);
						*(r.val) = std::stoi(token1);
					}
					else if (i == 1) {
						token2 = s.substr(0, pos);
						*(r.continent) = std::stoi(token2);
						regCont[token1] = token2;
					}
					else if (i > 1) {
						token3 = s.substr(0, pos);
						Region n(std::stoi(token3), -1);
						r.next->push_back(n);
					}
					s.erase(0, pos + delimiter.length());
					i++;
				}
				if (i == 1) {
					token2 = s;
					*(r.continent) = std::stoi(token2);
					regCont[token1] = token2;
					//*((regions->rbegin())->continent) = std::stoi(token2);
					//*(r.continent) = std::stoi(token2);
				}
				else if (i > 1) {
					token3 = s.substr(0, pos);
					Region n(std::stoi(token3), -1);
					r.next->push_back(n);
					//(regions->rbegin())->next->push_back(n);
					//r.next->push_back(n);
				}

				// std::cout << token1 << " " << token2 << std::endl;

				/*
				std::string ss = line;
				std::string dd = ":";

				size_t pp = 0;
				std::string tt;
				while ((pp = ss.find(dd)) != std::string::npos) {
					tt = ss.substr(0, pp);
					std::cout << "tt " << tt << std::endl;
					ss.erase(0, pp + dd.length());
				}
				std::cout << "ttt " << ss << std::endl;
				*/

			}

			for (std::list<Region>::iterator it = gameMap->eightMinEmpMap->begin(); it != gameMap->eightMinEmpMap->end(); ++it) {
				if (*(it->val) == startingRegionVal) {
					it->setStartingRegion(true);
					gameMap->setStartingRegion(&(*it));
				}
				for (std::list<Region>::iterator itNeigh = it->next->begin(); itNeigh != it->next->end(); ++itNeigh) {
					if (*(itNeigh->continent) == -1) {
						*(itNeigh->continent) = std::stoi(regCont.find(std::to_string(*(itNeigh->val)))->second);
					}
				}
			}
			/*
			for (std::list<Region>::iterator it = gameMap.eightMinEmpMap->begin(); it != gameMap.eightMinEmpMap->end(); ++it) {
				it->display();
			}
			*/
		}
	}


	/*
	std::cout << "-------------------------- " << std::endl;
	std::map<std::string, string>::iterator it = regCont.begin();
	while (it != regCont.end())
	{
		std::cout << it->first << " :: " << it->second << std::endl;
		it++;
	}
	*/

	inFile.close();

	/*

	inFile.open(fileName);
	if (!inFile) {
		cout << "Cannot open this file.";
		cout << "The program will now exit";
		exit(1);

	}


	while (getline(inFile, line)) {

		std::string s = line;
		std::string delimiter = ":";

		size_t pos = 0;
		std::string token1, token2;
		int i = 0;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			if (i == 0) {
				token1 = s.substr(0, pos);
			}
			if (i == 1) {
				token2 = s.substr(0, pos);
			}
			// std::cout << token << std::endl;
			s.erase(0, pos + delimiter.length());
			i++;
		}
		if (i == 1) {
			token2 = s;
		}
		std::cout << token1 << " " << token2 << std::endl;
		Region r(std::stoi(token1), std::stoi(token2));
		regions->push_back(r);


	}
	*/

	//char str[100];

	//int regVal;
	//int regC;
	//while (!inFile.eof()) {

	//	inFile >> *str;

	//	char* token = strtok(str, ":");
	//	

	//}

	return gameMap;

}

string MapLoader::readFolder(string fileName)
{
	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir(fileName.c_str())) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			//printf("%s %s\n", ent->d_name, ent->d_type); 32768
			if (ent->d_type == 32768) {
				std::cout << ent->d_name << " " << ent->d_type << endl;
			}
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		perror("");
		//return EXIT_FAILURE;
	}
	return string();
}

void MapLoader::mapLoader()
{
	//map = new Map();
	map = Map::getInstance();
}

