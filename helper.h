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
#include "tuple.h"



std::vector<tuple<std::string>> getStrings() {

	std::vector<tuple<std::string>> myVector;
 	
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

		myVector.push_back(tuple<std::string>(first,second));

	}

	return myVector;
}

void lcs(tuple<std::string> strings) {

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

	int letter = L[m][n];

	char LCS[letter+1];
	LCS[letter] = '\0';

	int i = m, j = n;
	while (i > 0 && j > 0)
	{
		if (strings.s1[i-1] == strings.s2[j-1])
		{
			LCS[letter-1] = strings.s1[i-1];
			i--;
			j--;
			letter--;
		}

		else if (L[i-1][j] >= L[i][j-1])
			i--;
		else
			j--;
	}

	std::cout << L[m][n] << " " << LCS << std::endl;
}


void backtrackLCS(int **L, int i, int j, tuple<std::string> strings, std::vector<tuple<int>> indices, int max) {

  //std::cout<<"in the backtrack"<<std::endl;

  if (L[i][j] == 0) {   
    if (indices.size() == max) {
      std::cout << "(";
      for (int i = indices.size()-1; i >= 0; i--) {
	indices[i].toString();
	if (i != 0)
	  std::cout<< ", ";
	else
	  std::cout<< ")\n";
      }
      return;
    }
    else
      return;
    
  }
    
  if (strings.s1[i-1] == strings.s2[j-1]) {
    indices.push_back(tuple<int>(i,j));
    //std::cout<<"going diag"<<std::endl;
    backtrackLCS(L, i-1, j-1, strings, indices, max); //go diagonal

    indices.pop_back();
    if (L[i-1][j] >= L[i][j-1]) {
      backtrackLCS(L, i-1, j, strings, indices, max); //go left
    }
    
  
    if (L[i][j-1] >= L[i-1][j]) {
      backtrackLCS(L, i, j-1, strings, indices, max); //go up
    }
  }

  /* else if (L[i][j-1] == L[i-1][j]) { //go left and up */
  /*   backtrackLCS(L, i, j-1, strings, indices, max); */
  /*   backtrackLCS(L, i-1, j, strings, indices, max); */
  //}
  else
    {
  if (L[i-1][j] >= L[i][j-1]) {
    //std::cout<<"going left"<<std::endl;
    backtrackLCS(L, i-1, j, strings, indices, max); //go left
  }
    
  
  if (L[i][j-1] >= L[i-1][j]) {
    //std::cout<<"going up"<<std::endl;
    backtrackLCS(L, i, j-1, strings, indices, max); //go up
  }
    }
}

void lcsALL(tuple<std::string> strings) {


	int m = strings.s1.length(); //rows
	int n = strings.s2.length(); //columns

	int **L; //instantiate 2d matrix
	L = new int *[m+1];
	for (int i = 0; i < m+1; i++)
	  L[i] = new int[n+1];

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

	std::vector<tuple<int>> indices;
	//std::cout<<"entering backtrack"<<std::endl;
	backtrackLCS(L, m, n, strings, indices, L[m][n]);

}



#endif
