# include <iostream>
#include <algorithm>

/* ALGORITMO IS_SORTED */
template<typename T>
bool is_sorted(const std::vector<T>& vec) {
	bool ord = true; // inizializzo variabile booleana 
	if (vec.size() == 0) {
		return ord; // se il vettore ha dimensione 0 è ordinato
	}
	for (int i = 0; i < vec.size() - 1; i++) {
		if (vec[i] > vec[i+1]) { // controllo a due a due
			ord = false;
			return ord;
		}
	}
	return ord;
}

/* ALGORITMO BUBBLESORT */
/* (confronto elementi a due a due, se ne trovo due in ordine errato li scambio) */
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
/* (scorro il vettore un elemento alla volta, facendolo "scivolare" all'indietro fino alla sua posizione corretta) */
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
/* (cerco ciclicamente il valore minimo assoluto nella porzione non ancora ordinata) */
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