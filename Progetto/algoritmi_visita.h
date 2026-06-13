#pragma once
#include "undirected_graph.h"
#include <vector>
#include <set>
#include <limits> // usare infinito
#include <queue> // usare priority queue

// BFS, DFS
template <typename T, typename contenitore> 
// T è tipo oggetti nodi dentro grafo, contenitore è tipo contenitore (coda/pila)

// algoritmo di visita unico per lifo e fifo (cambia a seconda del tipo)
undirected_graph<T> graph_visit(const undirected_graph<T>& G, const T& v, contenitore& c) {
	
	// inizializzo l'albero risultante, l'insieme dei nodi visitati e la mappa dei predecessori
	undirected_graph<T> albero_visita; 
	std::set<T> visitati; 
	std::map<T,T> predecessore; // salvo predecessori: devo ricostruire albero visita
	
	// inserisco il nodo di partenza nel contenitore
	c.put(v);
	
	// finchè il contenitore (coda o stack) non è vuoto
	while(! c.empty()) {
		
		// funzione get implementata nella classe (diversa a seconda del tipo di c)
		T u = c.get(); 
		
		// inseriamo il nodo estratto u, nell'insieme dei nodi visitati
		visitati.insert(u);
	
		// ciclo sui vicini di u
		for(auto& w : G.neighbours(u)) {
			
			// controllo se nodo non ancora stato visitato
			if(visitati.find(w) == visitati.end()) {
				
				// se non ancora visitato, lo inserisco nel contenitore
				c.put(w); 
				
				// salvo come predecessore nodo che lo ha scoperto
				if (predecessore.find(w) == predecessore.end()) { 
					predecessore[w] = u;
				}
			}
		}
	}
	
	// ciclo sui predecessori per ricostruire il grafo DFS/BFS
	for(auto& nodo : predecessore) {
	  albero_visita.add_edge(nodo.first, nodo.second);
	}
	
	// restituisco l'albero finale
	return albero_visita;
}


//DFS RICORSIVA
template <typename T>

// funzione ausiliaria per la ricorsione nella DFS
void ricorsione(const undirected_graph<T>& G, const T& nodo_corrente,
 std::set<T>& visitati, undirected_graph<T>& albero_visita) {
	
	// inserisco il nodo corrente nell'insieme dei nodi visitati
	visitati.insert(nodo_corrente); 
	
	// ciclo sui vicini del nodo corrente
	for(auto& w : G.neighbours(nodo_corrente)) {
		
		// se non ancora visitato, richiamo la ricorsione su quel nodo
		if (visitati.find(w) == visitati.end()) {
			// aggiungo l'arco con il nodo non ancora visitato w
			albero_visita.add_edge(nodo_corrente, w);
			ricorsione(G, w, visitati, albero_visita);
			// per ogni vicino non visitato "vado in profondità": (cfr. salto del cavallo)
			// aggiungo arco all'albero di visita e diventa lui nodo_corrente
		}
	}
 }

template <typename T>
// T è tipo oggetti nodi dentro grafo
undirected_graph<T> recursive_dfs(const undirected_graph<T>& G, const T& v) {
	
	// inizializzo l'albero finale
	undirected_graph<T> albero_visita; 
	// inizializzo insieme dei nodi visitati
	std::set<T> visitati;
	// ricorsione 
	ricorsione(G, v, visitati, albero_visita);
	
	return albero_visita;
}


//DIJKSTRA
template <typename T>
// prende in entrata il grafo G e il nodo di partenza s 
undirected_graph<T> Dijkstra(const undirected_graph<T>& G, const T& s) {
	// inizializzo tutte le strutture necessarie
	undirected_graph<T> albero_visita; 
	std::vector<T> nodi = G.all_nodes();
	std::map<T,T> predecessore; 
	std::map<T,int> distanza_sorgente;
	
	// inizializzo le distanze e i predecessori
	int infinito = std::numeric_limits<int>::max();
	for(auto& nodo : nodi) {
		distanza_sorgente[nodo] = infinito;
	}
	predecessore[s] = s; 
	distanza_sorgente[s] = 0;
	
	// definisco la priority queue del metodo
	std::priority_queue<std::pair<int,T>, std::vector<std::pair<int,T>>, std::greater<std::pair<int,T>>> coda_priorità; 
	// metto in coda coppie nodo-distanza: Ordino rispetto alla distanza minore dalla sorgente --> utilizzo come comparatore greater
	
	// ciclo sui nodi del grafo e inizializzo la priority queue
	for(auto& nodo : nodi) {
		coda_priorità.push({distanza_sorgente[nodo], nodo});
	}
	
	// ciclo finchè la queue non è vuota
	while(! coda_priorità.empty()) {
		// estraggo u come secondo elemento della coppia in cima alla coda 
		T u = coda_priorità.top().second;
		// estraggo la distanza di u dalla sorgente in modo analogo
		int dist_u = coda_priorità.top().first;
		// elimino la coppia (u,dist_u) dalla queue
		coda_priorità.pop();
		
		// se la nuova distanza è peggiore, vado all'iterazione successiva
		if (dist_u > distanza_sorgente[u]) {
			continue;
		}
		// non considero nodi con distanza maggiore di quella migliore trovata 
		
		// se la nuova distanza è migliore, questo diventa il nuovo percorso migliore
		// (per quali vicini di u, mi conviene passare da u)
		for(auto& w : G.neighbours(u)) {
			if(distanza_sorgente[w] > (dist_u + 1)) {
				distanza_sorgente[w] = dist_u + 1;
				predecessore[w] = u;
				coda_priorità.push({distanza_sorgente[w], w});
				//salvo duplicato nella coda, avrà priorità più bassa di quello già presente
				//--> estratto prima
				//--> per non riconsiderarlo quando verrà estratto aggiungo controllo sopra:
				
			}
		}
	}
	// ricostruisco tramite la mappa mappa predecessore, l'albero risultante
	for(auto& nodo : predecessore) {
		if(nodo.first != s) // la sorgente non ha predecessori
		  albero_visita.add_edge(nodo.first, nodo.second);
			}
	return albero_visita;
}