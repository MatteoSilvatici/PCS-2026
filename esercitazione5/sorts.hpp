# include <iostream>
#include <algorithm>
#include <random>
#include <limits>

/* ALGORITMO IS_SORTED */
template<typename T>
bool is_sorted(const std::vector<T>& vec) {
	bool ord = true; // inizializzo variabile booleana 
	if (vec.size() <= 1) {
		return ord; // se il vettore ha dimensione <=1 è ordinato
	}
	for (int i = 0; i < vec.size() - 1; i++) {
		if (vec[i] > vec[i+1]) { // controllo a due a due
			ord = false;
			return ord;
		}
	}
	return ord;
}

/* ALGORITMO BUBBLESORT (O(n^2))*/
/* (confronto elementi a due a due, se ne trovo due in ordine errato li scambio) */
template<typename T>
void bubblesort(std::vector<T>& vec) {
	for (int i = 0; i < vec.size()-1; i++) { // i = posizione che voglio riempire correttamente
		for (int j = vec.size() - 1; j > i; j--) { // parto dal fondo e controllo coppia per coppia
			if (vec[j] < vec[j-1]) {
				T temp = vec[j];
				vec[j] = vec[j-1];
				vec[j-1] = temp;
			}
		}
	}
	return;
} 

/* ALGORITMO INSERTION-SORT (O(n^2))*/
/* (scorro il vettore un elemento alla volta, facendolo "scivolare" all'indietro fino alla sua posizione corretta) */
template<typename T>
void insertion_sort(std::vector<T>& vec) {
	for (int j = 1; j < vec.size(); j++) { // parto dal secondo elemento
		T key = vec[j];
		int i = j-1;
		while (i >= 0 && vec[i] > key) { // vado avanti finchè non ne trovo uno più piccolo (o finisce lo spazio)
			vec[i+1] = vec[i];
			i = i-1;
		}
		vec[i+1] = key; 
	}
	return;
}


/* ALGORITMO SELECTION-SORT (O(n^2))*/
/* (cerco ciclicamente il valore minimo assoluto nella porzione non ancora ordinata) */
template<typename T>
void selection_sort(std::vector<T>& vec) {
	for (int i = 0; i < vec.size() - 1; i++) {
		int min = i;
		for (int j = i+1; j < vec.size(); j++) { // cerco l'indice del valore più piccolo nella parte non ancora ordinata
			if (vec[j] < vec[min]) {
				min = j;
			}
		}
		T temp = vec[i]; // quindi scambio con l'elemento in posizione i
		vec[i] = vec[min];
		vec[min] = temp;
	}
	return;
}



/* ALGORITMO QUICKSORT (O(n*log(n)))*/
/* (sceglie un elemento pivot, sposta tutti gli elementi più piccoli a sinistra
    e quelli più grandi a destra, restituendo la posizione finale del pivot) */
template<typename T>
int Partition(std::vector<T>& vec, int sx, int dx, int p) {
	if (p != dx) {
		std::swap(vec[p], vec[dx]);
		p = dx;
	}
	int i = sx - 1;
	for (int j = sx; j <= dx-1; j++) {
		if (vec[j] <= vec[p]) {
			i++;
			std::swap(vec[i], vec[j]);
		}
	}
	if (i != dx) {
		std::swap(vec[i+1], vec[dx]);
	}
	return(i+1); // ritorno il rango
}

/* (chiama ricorsivamente se stessa sulle due metà create dalla partizione) */
template<typename T>
void quicksort(std::vector<T>& vec, int sx, int dx) {
	if (sx < dx) {
		int p = std::rand() % (dx-sx+1) + sx; // scelta elemento pivot (decomposizione)
		int q = Partition(vec, sx, dx, p); // calcolo del rango (posizione elemento p nel vettore ordinato)
		quicksort(vec, sx, q-1);
		quicksort(vec, q+1, dx); // infine ricorsione
	}
}


/* ALGORITMO MERGESORT (O(n*log(n)))*/
/* (prende le due metà già ordinat, le copia in vettori temporanei (L e R)
    e le fonde insieme nel vettore originale mettendole in ordine) */
template<typename T>
void merge(std::vector<T>& vec, int sx, int c, int dx) {
	int n1 = c-sx+1;
	int n2 = dx-c;
	std::vector<T> L(n1);
	std::vector<T> R(n2);
	for (int i = 0; i < n1; i++) {
		L[i] = vec[sx+i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = vec[c+1+j];
	}
	int i = 0;
	int j = 0;
	int k = sx;
	while (i < n1 && j < n2) { // confronto dei termini "in comune"
		if (L[i] <= R[j]) {
			vec[k] = L[i];
			i++;
		}
		else {
			vec[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) { // se R ha meno elementi, L ha ancora elementi, quindi li copio su vec
		vec[k++] = L[i++]; // assegno valore e poi incremento k,i
	}
	while (j < n2) { // se L ha meno elementi, R ne ha ancora, quindi li copio su vec
		vec[k++] = R[j++]; // assegno valore e poi incremento k,j
	}	
}

/* (divide il vettore a metà ricorsivamente finchè non rimangono singoli elementi) */
template<typename T>
void mergesort(std::vector<T>& vec, int sx, int dx) {
	if (sx < dx) {
		int c = floor((sx+dx)/2);
		mergesort(vec,sx,c);
		mergesort(vec,c+1,dx);
		merge(vec,sx,c,dx);
	}
}


/* ALGORITMO QUICKSORT MODIFICATO */

/* (versione insertion sort usata per quicksort che lavora solo su una specifica porzione del vettore) */
template<typename T>
void insertion_sort_range(std::vector<T>& vec, int sx, int dx) {
    for (int j = sx + 1; j <= dx; j++) { // inizio dal secondo elemento della porzione (sx), fino alla fine (dx)
        
		T key = vec[j]; // salvo il valore "corrente" da inserire nella parte ordinata
        int i = j - 1; // parto a controllare dall'elemento subito alla sua sinistra
        
		while (i >= sx && vec[i] > key) { // finché non raggiunge l'inizio della porzione e trova elementi più grandi della key
            
			vec[i + 1] = vec[i]; // sposta l'elemento a destra per fare spazio
            i = i - 1; // passa all'elemento precedente
        }
        vec[i + 1] = key; // inserisco la key nella posizione corretta trovata
    }
}

/* (se n<=60 si usa l'insertion sort, altrimenti si usa il quicksort classico) */
template<typename T>
void quicksort_ibrido(std::vector<T>& vec, int sx, int dx) {
    int SOGLIA = 60; // valore trovato dai test precedenti
    
    if (dx - sx + 1 < SOGLIA) {
        insertion_sort_range(vec, sx, dx); // uso l'algoritmo per piccoli vettori
    } 
	
    else if (sx < dx) {
        int p = std::rand() % (dx - sx + 1) + sx; // scelgo un pivot a caso tra sx e dx
        int q = Partition(vec, sx, dx, p); // organizzo il vettore attorno al pivot 
        quicksort_ibrido(vec, sx, q - 1);
        quicksort_ibrido(vec, q + 1, dx); 
    }
}