#pragma once
#include <vector>
#include <list>

template<typename T>
// definizione classe lifo (stack)
class lifo {
	
	// inizializzo il vettore dello stack
	std::vector<T> vettore; 
	
	public: 
	lifo() {} //costruttore default
	
	// metodi che inseriscono/rimuovono elementi alla fine (pila)
	void put(const T& elem) {
		vettore.push_back(elem);
	}
	
	T get() {
		T elem = vettore.back();
		vettore.pop_back();
		return elem; 
	}
	
	bool empty() { //verifica se pila vuota
		if (vettore.size() == 0) {
			return 1; 
		}
		return 0;
	}
};

// definizione classe fifo (queue)
template<typename T>
class fifo {
	
	// inizializzo la lista della coda
	std::list<T> lista; 
	
	public: 
	fifo() { //costruttore default
	}
	
	// metodi che inseriscono elementi alla fine ed estraggono dall'inizio (coda)
	void put(const T& elem) {
		lista.push_back(elem);
	}
	
	T get() {
		T elem = lista.front();
		lista.pop_front();
		return elem; 
	}
	
	bool empty() { //verifica se pila vuota
		if (lista.size() == 0) {
			return 1; 
		}
		return 0;
	}
};