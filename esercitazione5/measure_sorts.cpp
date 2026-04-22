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
	
	int n_vec = 100; // vettori richiesti 
	
	for (int size = 2; size <= 100; size += 1) {
		
		std::cout << "------------ vettori di dimensione: " << size << " ---------------" << "\n";
		
		std::vector<std::vector<int>> dataset(n_vec, std::vector<int>(size));
        
        for (int i = 0; i < n_vec; i++) {
            rf.fill(dataset[i], -10000, 10000);
        }
        
        std::vector<std::vector<int>> data_bubble = dataset;
        std::vector<std::vector<int>> data_insertion = dataset;
        std::vector<std::vector<int>> data_selection = dataset;
        std::vector<std::vector<int>> data_merge = dataset;
        std::vector<std::vector<int>> data_quick = dataset;
        std::vector<std::vector<int>> data_std = dataset;
		
		/* BUBBLESORT */
		tc.tic(); // inizio cronometro
		for (int i = 0; i < n_vec; i++) {
			bubblesort(data_bubble[i]); // sorting
		}
		double secs1 = tc.toc(); // fermo cronometro
		std::cout << "Elapsed time (bubblesort) : " << secs1/n_vec << " seconds\n";
		
		/* INSERTION-SORT */
		tc.tic(); // inizio cronometro
		for (int i = 0; i < n_vec; i++) {
			insertion_sort(data_insertion[i]); // sorting
		}
		double secs2 = tc.toc(); // fermo cronometro
		std::cout << "Elapsed time (insertion_sort) : " << secs2/n_vec << " seconds\n";
		
		/* SELECTION-SORT */
		tc.tic(); // inizio cronometro
		for (int i = 0; i < n_vec; i++) {
			selection_sort(data_selection[i]); // sorting
		}
		double secs3 = tc.toc(); // fermo cronometro
		std::cout << "Elapsed time (selection_sort) : " << secs3/n_vec << " seconds\n";
		
		/* MERGESORT */
        tc.tic();     
        for (int i = 0; i < n_vec; i++) {
			mergesort(data_merge[i], 0, size - 1);
		}
		double secs4 = tc.toc(); // fermo cronometro
        std::cout << "Elapsed time (mergesort) : " << secs4 / n_vec << " seconds\n";
        
        /* QUICKSORT */
        tc.tic();     
        for (int i = 0; i < n_vec; i++) {
			quicksort(data_quick[i], 0, size - 1);
		}
		double secs5 = tc.toc(); // fermo cronometro
        std::cout << "Elapsed time (quicksort) : " << secs5 / n_vec << " seconds\n";
        
        /* STD::SORT */
        tc.tic();     
        for (int i = 0; i < n_vec; i++) {
			std::sort(data_std[i].begin(), data_std[i].end());
		}
		double secs6 = tc.toc();
        std::cout << "Elapsed time (std::sort) : " << secs6 / n_vec << " seconds\n";
        
		/* QUICKSORT IBRIDO */
		tc.tic();     
        for (int i = 0; i < n_vec; i++) {
			quicksort_ibrido(data_quick[i], 0, size - 1);
		}
		double secs7 = tc.toc();
        std::cout << "Elapsed time (quicksort_ibrido) : " << secs7 / n_vec << " seconds\n";
        
    }
    
    return EXIT_SUCCESS;
}