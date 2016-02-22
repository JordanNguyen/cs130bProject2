#ifndef STRINGPAIR_H
#define STRINGPAIR_H
#include <iostream>
#include <string>

class stringPair {
private:
public:
	std::string s1;
	std::string s2;
	stringPair(std::string _s1, std::string _s2) { s1 = _s1; s2 = _s2; }
	~stringPair() {}

	void toString() {std::cout << s1 << " " << s2 << std::endl;}

};

#endif