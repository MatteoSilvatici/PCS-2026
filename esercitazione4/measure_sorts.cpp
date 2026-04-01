#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm> // per std::sort
#include "sorts.hpp"
#include "timecounter.h"
#include "randfiller.h"

int main(void)
{
	randfiller rf;
	timecounter tc;
	
	for (int size = 4; size <= 8192; size *= 2) {
		
		std::cout << "------------ vettori di dimensione: " << size << " ---------------" << "\n";
		
		std::vector<int> original_vec(size);
        rf.fill(original_vec, -10000, 10000);
        
        std::vector<int> vec1 = original_vec;
        std::vector<int> vec2 = original_vec;
        std::vector<int> vec3 = original_vec;
        std::vector<int> vec_std = original_vec;
		
		/* BUBBLESORT */
		tc.tic(); // inizio cronometro

		bubblesort(vec1); // sorting
    
		double secs1 = tc.toc(); // fermo cronometro
		std::cout << "Elapsed time (bubblesort) : " << secs1 << " seconds\n";
		
		/* INSERTION-SORT */
		tc.tic();     

		insertion_sort(vec2);
    
		double secs2 = tc.toc(); 
		std::cout << "Elapsed time (insertion_sort) : " << secs2 << " seconds\n";
		
		/* SELECTION-SORT */
		tc.tic();     

		selection_sort(vec3);
    
		double secs3 = tc.toc(); 
		std::cout << "Elapsed time (selection_sort) : " << secs3 << " seconds\n";
		
		/* STD::SORT */
		tc.tic();     

		std::sort(vec_std.begin(), vec_std.end());
    
		double secs4 = tc.toc(); 
		std::cout << "Elapsed time (std::sort) : " << secs4 << " seconds\n";
	}
    
    return EXIT_SUCCESS;
}