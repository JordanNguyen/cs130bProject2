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

void lcs(stringPair strings) {

	int m = strings.s1.length(); //rows
	int n = strings.s2.length(); //columns

	int L[m+1][n+1]; //instantiate 2d matrix

	//set column 0 to all zeros
	for (int q = 0; q <= m; q++)
		L[q][0] = 0;
	//set row 0 to all zeros
	for (int r = 0; r <= n; r++)
		L[0][r] = 0;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <=n; j++) {
			if (strings.s1[i-1] == strings.s2[j-1]) 
				L[i][j] = L[i-1][j-1] + 1;         //get diagonal + 1
			else if (L[i-1][j] >= L[i][j-1]) 
				L[i][j] = L[i-1][j];               //get upper value
			else
				L[i][j] = L[i][j-1];               //get left value
		}
	}

	int length = L[m][n];

	char LCS[length+1];
	LCS[length] = '\0';

	int i = m, j = n;
	while (i > 0 && j > 0)
	{
		if (strings.s1[i-1] == strings.s2[j-1])
		{
			LCS[length-1] = strings.s1[i-1];
			i--;
			j--;
			length--;
		}

		else if (L[i-1][j] >= L[i][j-1])
			i--;
		else
			j--;
	}

	std::cout << L[m][n] << " " << LCS << std::endl;
}


#endif