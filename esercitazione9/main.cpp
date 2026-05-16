#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include "grafi.hpp"
#include "stack_queue.hpp"

int main(void) {
	fifo<int> q;
	q.put(2);
	q.put(9);
	int x = q.get();
	bool e = q.empty();
	
	std::cout << x << " " << e << "\n";
	
	lifo<int> s;
	s.put(2);
	s.put(9);
	int y = s.get();
	bool f = s.empty(); 
	
	std::cout << y << " " << f << "\n";

	// inizializzazione grafo
    unidirected_graph<int> G;
    
    G.add_edge(unidirected_edge<int>{1, 2}); 
    G.add_edge(unidirected_edge<int>{1, 3});
	
    G.add_edge(unidirected_edge<int>{2, 4});
    G.add_edge(unidirected_edge<int>{2, 5});
    G.add_edge(unidirected_edge<int>{3, 5});
    G.add_edge(unidirected_edge<int>{3, 6});

    G.add_edge(unidirected_edge<int>{4, 7});
    G.add_edge(unidirected_edge<int>{5, 7});
    G.add_edge(unidirected_edge<int>{6, 7});
	
	std::vector<int> visitati_;
	// stampa per Graphviz
	std::cout << " -- grafo di partenza -- " << "\n";
	for (int u : G.all_nodes()) {
		visitati_.push_back(u); 
    
		for (int v : G.neighbours(u)) {
			// Se il vicino 'v' non è ancora stato processato, stampiamo la riga
			if (std::find(visitati_.begin(), visitati_.end(), v) == visitati_.end()) {
            std::cout << u << "--" << v << ";\n";
			}
		}
	}
	
	std::cout << " -- algoritmo BFS -- " << "\n";
	fifo<int> coda;
	auto albero_BFS = graph_visit(G, 1, coda); // Genera la visita in ampiezza
	
	std::cout << " -- algoritmo DFS -- " << "\n";
	lifo<int> pila;
	auto albero_DFS = graph_visit(G, 1, pila); // Genera la visita in profondità
	
	std::cout << "\n--- ALBERO DFS RICORSIVA ---\n";
	auto albero_ricorsivo = recursive_dfs(G, 1);
	
	std::vector<int> visitati__; 
	// stampa per Graphviz
	for (int u :  albero_ricorsivo.all_nodes()) {
		visitati__.push_back(u); 
    
		for (int v :  albero_ricorsivo.neighbours(u)) {
			// Se il vicino 'v' non è ancora stato processato, stampiamo la riga
			if (std::find(visitati__.begin(), visitati__.end(), v) == visitati__.end()) {
            std::cout << u << "--" << v << ";\n";
			}
		}
	}
	
	std::cout << " -- algoritmo Dijkstra --" << "\n";
	auto albero_Dijkstra = Dijkstra(G, 1);
	
	std::vector<int> visitati; 
	// stampa per Graphviz
	for (int u : albero_Dijkstra.all_nodes()) {
		visitati.push_back(u); 
    
		for (int v : albero_Dijkstra.neighbours(u)) {
			// Se il vicino 'v' non è ancora stato processato, stampiamo la riga
			if (std::find(visitati.begin(), visitati.end(), v) == visitati.end()) {
            std::cout << u << "--" << v << ";\n";
			}
		}
	}
	
	return 0;
}