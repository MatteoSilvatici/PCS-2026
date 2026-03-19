#include <iostream>
#include <algorithm>
#include <cmath>

int main() {
	static const int N = 10;
	double arr[N] = {3,5,6,7,1,2,4,9,8,10};
	// funzione minimo
	double min_arr = arr[0];
	for(int i=1; i<10; i+=1) {
		min_arr = std::min(min_arr,arr[i]);
	}
	std::cout << min_arr << "\n";
	
	// funzione massimo
	double max_arr = arr[0];
	for(int i=1; i<10; i+=1) {
		max_arr = std::max(max_arr,arr[i]);
	}
	std::cout << max_arr << "\n";
	
	// funzione media
	double sum = 0;
	for(int i=0; i<10; i+=1) {
		sum += arr[i];
	}
	double mean_arr = sum / N;
	std::cout << mean_arr << "\n";
	
	// funzione deviazione standard
	double sum_dev = 0;
	for(int i=0; i<10; i+=1) {
		sum_dev += (arr[i] - mean_arr)*(arr[i] - mean_arr);
	}
	double devst_arr = std::sqrt(sum_dev/(N-1));
	std::cout << devst_arr << "\n";
	
	return 0;
}