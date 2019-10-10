#include "BiddingFacility.h"
#include <iostream>

using namespace std;

std::string * BiddingFacility::playerColor()
{
	std::string i;
	std::cout << "Enter the color you wish to choose\n";
	std::cin >> i;
	std::cout << "Your color is now: " << i;

	return i;
}