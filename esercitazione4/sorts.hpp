# include <iostream>
#include <algorithm>

/* ALGORITMO IS_SORTED */
template<typename T>
bool is_sorted(const std::vector<T>& vec) {
	bool ord = true;
	if (vec.size() == 0) {
		return ord;
	}
	for (int i = 0; i < vec.size() - 1; i++) {
		if (vec[i] > vec[i+1]) {
			ord = false;
			return ord;
		}
	}
	return ord;
}

/* ALGORITMO BUBBLESORT */
template<typename T>
void bubblesort(std::vector<T>& vec) {
	if (vec.size() <= 1) return;
	for (int i = 0; i < vec.size()-1; i++) {
		for (int j = vec.size() - 1; j > i; j--) {
			if (vec[j] < vec[j-1]) {
				T temp = vec[j];
				vec[j] = vec[j-1];
				vec[j-1] = temp;
			}
		}
	}
	return;
}

/* ALGORITMO INSERTION-SORT */
template<typename T>
void insertion_sort(std::vector<T>& vec) {
	if (vec.size() <= 1) return;
	for (int j = 1; j < vec.size(); j++) {
		T key = vec[j];
		int i = j-1;
		while (i >= 0 && vec[i] > key) {
			vec[i+1] = vec[i];
			i = i-1;
		}
		vec[i+1] = key;
	}
	return;
}

/* ALGORITMO SELECTION-SORT */
template<typename T>
void selection_sort(std::vector<T>& vec) {
	if (vec.size() <= 1) return;
	for (int i = 0; i < vec.size() - 1; i++) {
		int min = i;
		for (int j = i+1; j < vec.size(); j++) {
			if (vec[j] < vec[min]) {
				min = j;
			}
		}
		T temp = vec[i];
		vec[i] = vec[min];
		vec[min] = temp;
	}
	return;
}