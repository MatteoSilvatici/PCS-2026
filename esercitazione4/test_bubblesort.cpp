#include <iostream>
#include <vector>
#include <string>
#include "sorts.hpp"
#include "randfiller.h"

template<typename T>
void
print_vector(const std::vector<T>& v)
{
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

int main() {
	/* TEST STRINGA */
	std:: vector<std::string> test_string = {"mela","pera","banana","pesca","albicocca","barca","rickroll","computer","montagna"};
	bubblesort(test_string);
	
	if (!is_sorted(test_string)) {
		std::cerr << "Ordinamento stringhe fallito" << std::endl;
		return EXIT_FAILURE;
	}
	
	/* TEST VETTORI */
	randfiller rf;
	
	std::vector<int> vdim;
    vdim.resize(100);
    rf.fill(vdim, 100, 1000); /* use it on vectors */
    print_vector(vdim);
	
	for(int i = 0; i < 100; i++) {
		std::vector<int> vi;
		vi.resize(vdim[i]);
		rf.fill(vi, -10000, 10000); 
		bubblesort(vi);
		if (!is_sorted(vi)) {
			std::cerr << "Ordinamento stringhe fallito" << std::endl;
		return EXIT_FAILURE;
		}
		
		std::vector<float> vf;
		vf.resize(vdim[i]);
		rf.fill(vf, -10000.0f, 10000.0f);
		bubblesort(vf);
		if (!is_sorted(vf)) {
			std::cerr << "Ordinamento stringhe fallito" << std::endl;
		return EXIT_FAILURE;
		}

		std::vector<double> vd;
		vd.resize(vdim[i]);
		rf.fill(vd, -10000.0, 10000.0);
		bubblesort(vd);
		if (!is_sorted(vd)) {
			std::cerr << "Ordinamento stringhe fallito" << std::endl;
		return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}