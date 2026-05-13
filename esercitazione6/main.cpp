#include <iostream>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <cstdlib> // Necessario per EXIT_SUCCESS ed EXIT_FAILURE
#include "grafi.hpp"

int main() {
    std::cout << "INIZIO TEST AUTOMATIZZATI GRAFO\n\n";

    // --- TEST 0: Inizializzazione Archi ---
    std::list<unidirected_edge<int>> archi;
    for (int i = 0; i < 10; i++) {
        for (int j = i+1; j < 10; j++) {
            archi.push_back(unidirected_edge<int>(i,j)); 
        }
    }
    archi.push_back(unidirected_edge<int>(10, 2));

    // Un grafo completo di 10 nodi ha 45 archi, + 1 arco finale = 46.
    if (archi.size() != 46) {
        std::cerr << "[ERRORE] Test 0 Fallito: numero di archi generati errato (" << archi.size() << " invece di 46)\n";
        exit(EXIT_FAILURE); 
    }
    std::cout << "[OK] Test 0: Creazione base degli archi passata.\n";


    // Preparazione Grafi
    unidirected_graph<int> G1;
    unidirected_graph<int> G2;

    G1.add_edge(unidirected_edge<int>(1, 2));
    G1.add_edge(unidirected_edge<int>(2, 3));
    G1.add_edge(unidirected_edge<int>(3, 4));
    
    G2.add_edge(unidirected_edge<int>(2, 2)); // anello da un nodo in sè stesso
    G2.add_edge(unidirected_edge<int>(2, 3));
    G2.add_edge(unidirected_edge<int>(1, 3));

    // --- TEST 1: Comportamento Base (Aggiunta e Lettura) ---
    if (G1.all_edges().size() != 3) {
        std::cerr << "[ERRORE] Test 1 Fallito: G1 dovrebbe avere 3 archi!\n";
        exit(EXIT_FAILURE);
    }
    if (G2.all_edges().size() != 3) {
        std::cerr << "[ERRORE] Test 1 Fallito: G2 dovrebbe avere 3 archi!\n";
        exit(EXIT_FAILURE);
    }

    // Controllo i vicini del nodo 2 in G1 (dovrebbero essere 1 e 3)
    std::set<int> vicini_G1_2 = G1.neighbours(2);
    if (vicini_G1_2.size() != 2 || vicini_G1_2.find(1) == vicini_G1_2.end() || vicini_G1_2.find(3) == vicini_G1_2.end()) {
        std::cerr << "[ERRORE] Test 1 Fallito: Vicini del nodo 2 in G1 errati!\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "[OK] Test 1: Comportamento base e adiacenze verificati.\n";


    // --- TEST 2: Gestione dei Duplicati ---
    G1.add_edge(unidirected_edge<int>(1, 2)); // Arco duplicato
    
    if (G1.all_edges().size() != 3) {
        std::cerr << "[ERRORE] Test 2 Fallito: Inserito un duplicato ma il numero di archi e' cambiato!\n";
        exit(EXIT_FAILURE);
    }

    std::set<int> vicini_G1_1 = G1.neighbours(1);
    // Il nodo 1 ha come vicino solo il nodo 2. Deve esserci 1 solo vicino.
    if (vicini_G1_1.size() != 1 || vicini_G1_1.find(2) == vicini_G1_1.end()) {
        std::cerr << "[ERRORE] Test 2 Fallito: Errore nei vicini dopo inserimento duplicato!\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "[OK] Test 2: Inserimento duplicati bloccato con successo.\n";


    // --- TEST 3: I casi limite dell'Operatore Differenza ---
    unidirected_graph<int> G3;
    G3.add_edge(unidirected_edge<int>(2, 3)); // In comune con G1
    G3.add_edge(unidirected_edge<int>(8, 9)); // Esclusivo di G3
    
    unidirected_graph<int> G_diff = G1 - G3;
    
    // G1 ha (1-2), (2-3), (3-4). G3 ha (2-3), (8-9). 
    // G1 - G3 deve avere 2 archi: (1-2) e (3-4)
    if (G_diff.all_edges().size() != 2) {
        std::cerr << "[ERRORE] Test 3 Fallito: Dimensione G_diff errata (" << G_diff.all_edges().size() << " invece di 2)\n";
        exit(EXIT_FAILURE);
    }

    // Sottrazione totale (G1 - G1) -> 0 archi
    unidirected_graph<int> G_vuoto = G1 - G1;
    if (G_vuoto.all_edges().size() != 0) {
        std::cerr << "[ERRORE] Test 3 Fallito: La sottrazione di un grafo da se stesso non produce un grafo vuoto!\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "[OK] Test 3: Operatore differenza ha calcolato i risultati corretti.\n";
	
	// se arrivo qua è tutto ok
    std::cout << "   TUTTI I TEST SUPERATI CON SUCCESSO   \n";

    return EXIT_SUCCESS;
}