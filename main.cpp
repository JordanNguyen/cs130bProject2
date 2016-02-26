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
	  }
	else
	{
		for (int i = 0; i < pairs.size(); i++)
			lcs(pairs[i]);
	}

	return 0;
}
