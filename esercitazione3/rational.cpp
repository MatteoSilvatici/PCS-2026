#include <iostream>
#include "rational.hpp"
#include <concepts>

int main(void) {
	rational<int> r1;
	std::cout << "costruttore di default: " << r1 << "\n";
	
	rational<int> r2(3,6);
	std::cout << "frazione 3/6: " << r2 << "\n";
	
	rational<int> r3(2,-4);
	std::cout << "frazione 2/-4: " << r3 << "\n";
	
	std::cout << "metodi num() e den() di 3/6: " << r2.num() << " " << r2.den() << "\n\n";
	
	rational<int> a(1,2);
	rational<int> b(1,4);
	rational<int> c = a+b;
	rational<int> d = a-b;
	rational<int> e = a*b;
	rational<int> f = a/b;
	std::cout << "a = " << a << ", b = " << b << "\n";
    std::cout << "a + b = " << c << "\n"; 
    std::cout << "a - b = " << d << "\n"; 
    std::cout << "a * b = " << e << "\n"; 
    std::cout << "a / b = " << f << "\n\n"; 
	
	rational<int> r_inf(5,0);
	rational<int> r_nan(0,0);
	rational<int> r_num(5,2);
	rational<int> r_zero(0,1);
	std::cout << "Creazione 5/0 (Inf): " << r_inf << "\n";
    std::cout << "Creazione 0/0 (NaN): " << r_nan << "\n\n";
	
	rational<int> g = r_num + r_inf;
	rational<int> h = r_num + r_nan;
	rational<int> i = r_inf + r_inf;
	rational<int> l = r_zero*r_inf;
	rational<int> m = r_inf/r_inf;
	std::cout << r_num << " + Inf = " << g << "\n"; 
    std::cout << r_num << " + NaN = " << h << "\n"; 
    std::cout << r_inf << " + Inf = " << i << "\n";
	std::cout << "0 * Inf = " << l << "\n"; 
    std::cout << "Inf / Inf = " << m << "\n";
	return 0;
}