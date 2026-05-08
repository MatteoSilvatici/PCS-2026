#include <iostream>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
# include "grafi.hpp"

int main() {
	std::list<unidirected_edge<int>> archi;
	
	for (int i = 0; i < 10; i++) {
		for (int j = i+1; j < 10; j++) {
			unidirected_edge<int> nuovo_arco(i,j); // creo il nuovo arco
			archi.push_back(nuovo_arco); // lo aggiungo in fondo alla lista
		}
	}
	
	unidirected_edge<int> arco_invertito(10, 2); 
	archi.push_back(arco_invertito);

	std::cout << "Lista degli archi creati:" << std::endl;
	for (const auto& arco : archi) {
		std::cout << arco << std::endl;
	}

	std::cout << "=== INIZIO TEST GRAFO NON ORIENTATO ===\n\n";

    unidirected_graph<int> G1;
	unidirected_graph<int> G2;

    // ---------------------------------------------------------
    std::cout << "--- TEST 1: Comportamento Base (Aggiunta e Lettura) ---\n";
    G1.add_edge(unidirected_edge<int>(1, 2));
    G1.add_edge(unidirected_edge<int>(2, 3));
    G1.add_edge(unidirected_edge<int>(3, 4));
	
	G2.add_edge(unidirected_edge<int>(2, 2));
	G2.add_edge(unidirected_edge<int>(2, 3));
	G2.add_edge(unidirected_edge<int>(1, 3));
    
    std::cout << "Archi presenti in G1 (dovrebbero essere 3):\n";
    for (const auto& arco : G1.all_edges()) {
        std::cout << arco << " [ID: " << G1.edge_number(arco) << "]\n";
    }
	
	std::cout << "Archi presenti in G2 (dovrebbero essere 3):\n";
    for (const auto& arco : G2.all_edges()) {
        std::cout << arco << " [ID: " << G2.edge_number(arco) << "]\n";
    }
    
    std::cout << "\nI vicini del nodo 2 in G1 (dovrebbero essere 1 e 3):\n";
    for (int vicino : G1.neighbours(2)) {
        std::cout << vicino << " ";
    }
	
	std::cout << "\nI vicini del nodo 2 in G2 (dovrebbero essere 2 e 3):\n";
    for (int vicino : G2.neighbours(2)) {
        std::cout << vicino << " ";
    }
    std::cout << "\n\n";

    // ---------------------------------------------------------
    std::cout << "--- TEST 2: Gestione dei Duplicati ---\n";
    std::cout << "Provo ad aggiungere di nuovo l'arco (1 -- 2)\n";
    G1.add_edge(unidirected_edge<int>(1, 2));
    
    std::cout << "Numero totale di archi attesi: 3. Attuali: " << G1.all_edges().size() << "\n";
    std::cout << "I vicini del nodo 1 (dovrebbe essere solo il 2):\n";
    for (int vicino : G1.neighbours(1)) {
        std::cout << vicino << " ";
    }
    std::cout << "\n\n";

    // ---------------------------------------------------------
    std::cout << "--- TEST 3: I casi limite dell'Operatore Differenza ---\n";
    unidirected_graph<int> G3;
    G3.add_edge(unidirected_edge<int>(2, 3)); // In comune con G1
    G3.add_edge(unidirected_edge<int>(8, 9)); // Esclusivo di G2
    
    std::cout << "Eseguo G_diff = G1 - G2\n";
    unidirected_graph<int> G_diff = G1 - G3;
    
    std::cout << "Archi nel risultato (attesi (1--2) e (3--4). L'arco (8--9) viene ignorato):\n";
    for (const auto& arco : G_diff.all_edges()) {
        std::cout << arco << "\n";
    }

    std::cout << "\nSottrazione totale (G1 - G1). Archi attesi nel risultato: 0.\n";
    unidirected_graph<int> G_vuoto = G1 - G1;
    std::cout << "Archi presenti: " << G_vuoto.all_edges().size() << "\n\n";

    std::cout << "\n=== TEST COMPLETATO CON SUCCESSO ===\n";
    return 0;
}

