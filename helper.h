#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cfloat>
#include <iomanip>
#include <algorithm>
#include <set>
#include "stringPair.h"

std::vector<stringPair> getStrings() {

	std::vector<stringPair> myVector;

	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	double inputs;
	iss >> inputs;
	//std::cout << inputs << std::endl;

	while (std::getline(std::cin, line) )
	{
		std::istringstream check(line);
		std::string first;
		std::string second;
		check >> first >> second;

		myVector.push_back(stringPair(first,second));

	}

	return myVector;
}

int lcs(std::vector<stringPair> strings) {

	int 

}

#endif