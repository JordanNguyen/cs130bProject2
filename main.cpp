#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cfloat>
#include <algorithm>
#include "helper.h"
#include "tuple.h"


int main(int argc, char *argv[]) {
	
	std::vector<tuple<std::string>> pairs;
	pairs = getStrings();
	std::string all = "-all";
	if (argc > 1 && argv[1] == all)
	  {
	    for (int i = 0; i < pairs.size(); i++)
	      { lcsALL(pairs[i]);
		std::cout<<"\n";
	      }
	    //	    std::cout<<"not ready."<<std::endl;
	  }
	else
	{
		for (int i = 0; i < pairs.size(); i++)
			lcs(pairs[i]);
	}

	// int **array;
	// array = new int *[10];
	// for (int i = 0; i < 10; i++)
	//   array[i] = new int[10];
	// array[0][0] = 10;
	// std::cout<<array[0][0]<<std::endl;

	return 0;
}
