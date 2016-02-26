#ifndef TUPLE_H
#define TUPLE_H
#include <iostream>
#include <string>

template <class T> class tuple {
	
	private:
	public:
		T s1;
		T s2;
		tuple(T x1, T y1) {s1 = x1; s2 = y1;}
		~tuple() {};

		void toString() const { std::cout<<"<" << s1 << ", " << s2 << ">"; }

		bool operator<(const tuple& rhs) const 
		{
   			return (s1 != rhs.s1 || s2 != rhs.s2);
		}

};

#endif