#pragma once
#include <iostream>
#include <list>
#include <map>
#include <limits>
#include <queue>
#include "grafi.hpp"

template<typename T>
class fifo {
	
	std::list<T> q;
	
public:
	// costruttore di default
	fifo() {}
	
	// metodo put()
	void put(T elemento) {
		q.push_back(elemento);
		return;
	}
	
	// metodo get()
	T get() {
		T primo = q.front();
		q.pop_front();
		return primo;
	}
	
	// metodo empty()
	bool empty() {
		return q.empty();
	}
};


template<typename T>
class lifo {
	
	std::list<T> s;
	
public:
	// costruttore di default
	lifo() {}
	
	// metodo put()
	void put(T elemento) {
		s.push_front(elemento);
		return;
	}
	
	// metodo get()
	T get() {
		T primo = s.front();
		s.pop_front();
		return primo;
	}
	
	// metodo empty()
	bool empty() {
		return s.empty();
	}
};

template <typename contenitore, typename T> // T sarà fifo o lifo 
unidirected_graph<T> graph_visit(const unidirected_graph<T>& G, int source_node, contenitore& c) {
	
	// inizializzo il vettore reached con n elementi tutti falsi
	std::map<T, bool> reached;
	
	// definisco il grafico risultante
	unidirected_graph<T> risultato;
	
	// inserisco il nodo di partenza nel contenitore
	c.put(source_node);
	
	// lo segno come visitato
	reached[source_node] = true;
	
	while (!c.empty()) {
		
		// estraggo il nodo dal contenitore
		T current = c.get();
		
		// considero tutti i nodi adiacenti di current
		auto vicini = G.neighbours(current);
		
		// esploro i nodi adiacenti
		for (T vicino : vicini) {
			
			// controllo se vicino è stato visitato
			if (!reached[vicino]) {
				
				// lo segno come visitato
				reached[vicino] = true;
				
				// lo metto nel contenitore
				c.put(vicino);
				
				// inserisco l'arco nel grafo risultante
				risultato.add_edge(unidirected_edge<T>(current, vicino));				
				std::cout << current << "--" << vicino << "\n";
			}
		}
	}
	
	return risultato;
	
}

// per questa funzione ho trovato uno pseudocodice online e ho preso spunto da quello
// --> https://profs.scienze.univr.it/~cicalese/ALGORITMI/2014-15/Lec6_Grafi-2.pdf
template <typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& G, T source_node) {
    // definisco la mappa reached e il grafo risultante
    std::map<T, bool> reached;
    unidirected_graph<T> risultato;
    
    // Funzione Lambda Ricorsiva
    // Le parentesi quadre [&] le permettono di vedere 'reached' e 'risultato'
    // Per far chiamare una lambda a se stessa le passo 'self' come parametro
	// -> void indica che questa funzione non restituisce nulla, ma modifica variabili esterne
    auto esplora = [&](auto& self, T u) -> void {
        
        // Segno il nodo in cui mi trovo come visitato
        reached[u] = true;
        
        // Esploro i vicini
        for (const T& v : G.neighbours(u)) {
            
            // Se il vicino non è stato visitato, mi ci "tuffo" dentro
            if (!reached[v]) {
                
                // Aggiungo l'arco all'albero risultante
                risultato.add_edge(unidirected_edge<T>{u, v});
                
                // Chiamata ricorsiva: la funzione chiama se stessa sul vicino ancora non visitato
                self(self, v);
            }
        }
    };
    
    // Faccio partire la reazione a catena dal nodo sorgente (entro nella funzione esplora)
    esplora(esplora, source_node);
    
    // A ricorsione finita, restituisco l'albero
    return risultato;
}


template <typename T>
unidirected_graph<T> Dijkstra(const unidirected_graph<T>& G, T s) {
	
	// definisco l'infinito
	double INF = std::numeric_limits<double>::infinity();
	
	// definisco le mappe dei predecessori e delle distanze
	std::map<T, double> dist;
	std::map<T, T> pred;
	
	// estraggo tutti i nodi dal grafo di partenza
	auto all_nodes = G.all_nodes();
	
	// inizializzo le distanze e i predecessori
	for (const T& nodo : all_nodes) {
		dist[nodo] = INF;
		// pred[nodo] = -1; (non posso perchè T potrebbe non essere un int
	}
	
	// definisco la priority queue <dist, T>, con greater per avere il minimo in cima
	std::priority_queue<std::pair<double, T>,
						std::vector<std::pair<double,T>>,
						std::greater<std::pair<double, T>>> PQ;
						
	// inizializzo il nodo di partenza s nei vettori
	pred[s] = s;
	dist[s] = 0;
	
	// inizializzo la priority queue
	for (const T& nodo : all_nodes) {
		PQ.push({dist[nodo], nodo});
	}
	
	// definisco il grafo risultante
	unidirected_graph<T> risultato;
	
	// ciclo principale
	while (!PQ.empty()) {
		
		// estraggo il nodo di distanza minore
		double d_u = PQ.top().first;
		T u = PQ.top().second;
		
		// elimino il nodo dalla PQ
		PQ.pop();
		
		// se abbiamo già trovato una distanza migliore, lo ignoriamo
		if (d_u > dist[u]) continue;
		
		// esploriamo i nodi vicini
		for (const T& w : G.neighbours(u)) {
			
			// controllo se la distanza dal vicino è maggiore del nodo in considerazione
			if (dist[w] > dist[u]) {
				
				// nel caso aggiorno le mappe dist e pred
				dist[w] = dist[u];
				pred[w] = u;
				
				// e modifico la priority_queue
				PQ.push({dist[w], w});
			}
		}
	}
	
	// costruzione albero risultante
	for (const T& nodo : all_nodes) {
		
		// controllo se il nodo è stato raggiunto e se non è il nodo sorgente
		if (pred.count(nodo) && pred[nodo] != nodo) {
		// la funzione .count() mi restituisce un booleano
			
			// nel caso aggiungo l'arco al grafo risultante
			risultato.add_edge(unidirected_edge<T>{pred[nodo], nodo});
		}
	}
	
	return risultato;
}