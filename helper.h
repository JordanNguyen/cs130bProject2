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

//global set holding all the lcs indices
std::set<std::vector<tuple<int>>> lcsIndices;

/* parse input strings */
std::vector<tuple<std::string>> getStrings() {

	//vector to store tuples of strings, used to iterate over by main
	std::vector<tuple<std::string>> myVector;
 	
	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	double inputs; //get the first line
	iss >> inputs;

	//parse through the rest of the lines
	while (std::getline(std::cin, line) )
	{
		std::istringstream check(line);
		std::string first;
		std::string second;
		check >> first >> second;

		//add the string tuple to the vector
		myVector.push_back(tuple<std::string>(first,second));

	}

	return myVector;
}

/*regular lcs function that returns the length and the string of lcs */
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

	//iterate through whole matrix
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <=n; j++) {
			if (strings.s1[i-1] == strings.s2[j-1])//if letters match
				L[i][j] = L[i-1][j-1] + 1;         //get diagonal + 1
			else if (L[i-1][j] >= L[i][j-1]) 
				L[i][j] = L[i-1][j];               //get upper value
			else
				L[i][j] = L[i][j-1];               //get left value
		}
	}

	int letter = L[m][n]; //index of what letter we are on, also the length of the LCS

	char LCS[letter+1];   //make a char array the length of the LCS string + 1 for null char
	LCS[letter] = '\0';   //set last char to null

	int i = m, j = n;
	while (L[i][j] != 0)  //keep going thru matrix as long as value isnt 0
	{
		if (strings.s1[i-1] == strings.s2[j-1]) //if the letters match
		{
			LCS[letter-1] = strings.s1[i-1];    //set the value at index 'letter' to that letter
			i--;								//decrement i and j to go diagonal
			j--;
			letter--;							//decrement the index of letter 
		}

		else if (L[i-1][j] >= L[i][j-1])        //go to the bigger of L and U
			i--;
		else
			j--;
	}

	std::cout << L[m][n] << " " << LCS << std::endl;
}

/* iterates through the whole set and all the vectors in the set and prints out */
void printSet() {
	//int size = lcsIndices.size();
	//std::cout<<"entering print\n";
	std::set<std::vector<tuple<int>>>::iterator it = lcsIndices.begin();
	for (it = lcsIndices.begin(); it != lcsIndices.end(); it++)
	{	
		std::cout << "(";
		for (int j = it->size()-1 ; j >= 0; j--) {
			it->at(j).toString();
			if (j != 0)
				std::cout<<", ";
			else
				std::cout<<")\n";
		}
	}

	return;
}

/*recursive backtrack function to get all LCS indices
takes in a 2d array, the current indices of i and j, the tuple of strings you are working on,
the tuple of indices for where the letters match, and the length of the lcs
*/
void backtrackLCS(int **L, int i, int j, tuple<std::string> strings, std::vector<tuple<int>> indices, int max) {

  //base case, only add to set if the number of indices tuples matches the length of the lcs
	if (L[i][j] == 0 || i == 0 || j == 0) {
		if (indices.size() == max)
		{
			lcsIndices.insert(indices);
			return;
		}
		else
			return;
	}

  //if the letters match  
  if (strings.s1[i-1] == strings.s2[j-1]) {
    indices.push_back(tuple<int>(i,j));               //add that index to the vector
    backtrackLCS(L, i-1, j-1, strings, indices, max); //go diagonal

    indices.pop_back();                               //after the first recursive call, remove the found index and explore left and up
    if (L[i-1][j] >= L[i][j-1]) {
      backtrackLCS(L, i-1, j, strings, indices, max); //go left
    }
    
  
    if (L[i][j-1] >= L[i-1][j]) {
      backtrackLCS(L, i, j-1, strings, indices, max); //go up
    }
  }

  //if the letters didnt match you must backtrack either left, up or possibly both
  else {
  	if (L[i-1][j] >= L[i][j-1]) {
    	backtrackLCS(L, i-1, j, strings, indices, max); //go left
  	}
    
  
  	if (L[i][j-1] >= L[i-1][j]) {
    backtrackLCS(L, i, j-1, strings, indices, max); //go up
  	}
  }
}

/*same as lcs function, except this calls
the recursive backtrack function at the end */
void lcsALL(tuple<std::string> strings) {


	int m = strings.s1.length(); //rows
	int n = strings.s2.length(); //columns

	int **L; 						//instantiate 2d matrix with pointers since you cant pass arrays in C
	L = new int *[m+1]; 			//L points to an an array of ints size m+1 (rows)
	for (int i = 0; i < m+1; i++)   //each m+1 row points to an array of ints size n+1 (columns)
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


	std::vector<tuple<int>> indices; //create blank vector to hold the indices of letters
	backtrackLCS(L, m, n, strings, indices, L[m][n]);
	printSet(); 					 //print the set of LCS indices
	lcsIndices.clear();              //clear out the set for the next strings
	return;

}



#endif
