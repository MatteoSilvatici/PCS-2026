#include <iostream>
#include "rational.hpp"
#include <concepts>

int main(void) {
	rational<int> r1(1,0);
	rational<int> r2(1,0);
	
	rational<int> r3 = r1-r2;
	
	std::cout << r3;
	return 0;
}