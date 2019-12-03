#include "Utility.h"
#include <string>
#include <iostream>

Utility::Utility()
{
}


Utility::~Utility()
{
}

int inputHandling(int *input, int min, int max)
{
	bool isInt;
	bool acceptableInput = false;

	do {
		try {
			std::cin >> *input;
			isInt = true;
			if (std::cin.fail()) { //cin in fail state
				isInt = false;
				std::cin.clear(); //get rid of fail state
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard 'bad' characters
				throw std::string("\nInput not recognized. Please try again.\nNew input: ");
			}
		}
		catch (std::string e) {
			std::cout << e;
		}

		if (isInt && (!(*input < min) && !(*input > max))) {
			acceptableInput = true;
		}
		else if (isInt) {
			std::cout << "\nInput out of bounds.\nNew input: ";
		}

	} while (!acceptableInput);

	return *input;
}
