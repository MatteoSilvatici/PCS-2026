#pragma once
#include "undirected_graph.h"
#include "algoritmi_visita.h"
#include <vector> 
#include <set>
#include <algorithm> // serve per std::count e std::find

//METODO BASATO SU DFS

template <typename T>
// funzione che costruisce un cammino tra due nodi nell'albero DFS (modifica path)
bool findpath(const undirected_graph<T>& DFS_tree, const T& u, const T& v,
 std::vector<T>& path, std::set<T>& visitati) {
	
	// inserisco nodo corrente nell'insieme dei nodi visitati e nel path
	visitati.insert(u);
	path.push_back(u);
	
	// mi fermo quando il nodo corrente corriponde al nodo di arrivo
	if (u == v) {
		return true; 
	}
	
	// ciclo sui vicini del nodo corrente
	for(auto& n : DFS_tree.neighbours(u)) {
		// se non ho ancora visitato un vicino, verifico che da quel nodo posso arrivare a v
		if(visitati.find(n) == visitati.end()) {
			if (findpath(DFS_tree, n, v, path, visitati)) {
				return true; 
			}
		}
	}
	
	// se nessun vicino del nodo corrente mi permette di arrivare a v, tolgo il nodo corrente da path
	path.pop_back();
	return false; 
}

// funzione principale che chiama findpath
template <typename T>
std::vector<std::vector<T>> DFS_cicli(const undirected_graph<T>& G) {
	
	// definisco il vettore dei cicli fondamentali (vettori di nodi)
	std::vector<std::vector<T>> cicli_fondamentali; 
	
	// creazione coalbero C 
	T root = G.all_nodes()[0]; // parto da nodo qualsiasi per effettuare visita DFS
	undirected_graph<T> DFS_tree = recursive_dfs(G, root);
	undirected_graph<T> C = G - DFS_tree; 
	
	// ciclo sugli archi del coalbero
	for(auto& edge : C.all_edges()) {
		// per ogni arco del coalbero trovo un ciclo fondamentale di G
		std::vector<T> ciclo; 
		std::set<T> visitati; 
		findpath(DFS_tree, edge.from(), edge.to(), ciclo, visitati); // trova il percorso tra i due nodi dell'arco di C
		ciclo.push_back(edge.from()); // alla fine aggiungo il nodo di partenza
		cicli_fondamentali.push_back(ciclo); // aggiungo il ciclo alla base
	}
	
	return cicli_fondamentali; 
}


//ALGORITMO DE PINA

// definizione del prodotto scalare in modulo 2 (booleano)
int prod_scalare_bool(std::vector<int>& S, std::vector<int>& P) {
	int sum = 0; 
	for(size_t i = 0; i < S.size(); i++) {
		sum += (S[i] * P[i]);
	}
	return (sum % 2); // sommo tutti i contributi del prodotto scalare e prendo il resto della divisione per 2
}

// definzione differenza simmetrica XOR (or esclusivo)
std::vector<int> differenza_simmetrica_bool(std::vector<int>& S, std::vector<int>& P) {
	// definisco il vettore risultante
	std::vector <int> vettore_diff(S.size());
	for(size_t i = 0; i < S.size(); i++) {
		if ((S[i] == 0 && P[i] == 1) || (S[i] == 1 && P[i] == 0)) {
			vettore_diff[i] = 1; // metto pari a 1 gli elementi non in comune
		}
		else {
			vettore_diff[i] = 0;
		}
	}
	return vettore_diff;
}

// algoritmo principale
template <typename T>
// restituisce vettore di cicli minimi (vettori di nodi)
std::vector<std::vector<T>> DePina_cicli(const undirected_graph<T>& G) {
	// estraggo cardinalità e elementi necessari
	int n = G.all_nodes().size(); // n é numero di nodi
	int m = G.all_edges().size(); // m è numero di archi
	int k = m - n + 1; // #cicli fondamentali
	std::vector<undirected_edge<T>> archiG = G.all_edges(); // OSS: archi già ordinati 
	std::vector<T> nodiG = G.all_nodes();
	
	// inzializzazione k vettori di supporto di lugnhezza m (vettore di vettori)
	std::vector<std::vector<int>> vettori_supporto(k); 
	for(int i = 0; i < k; i++) { // ciclo sui vettori e li inizializzo tutti nulli
		std::vector<int> s(m, 0);
		vettori_supporto[i] = s; 
	}
	
	// definizione coalbero C
	T root = nodiG[0]; 
	undirected_graph<T> DFS_tree = recursive_dfs(G, root);
	undirected_graph<T> C = G - DFS_tree;
	std::vector<undirected_edge<T>> archi_C = C.all_edges();
	
	// riempimento vettori di supporto
	for(int i = 0; i < k; i++) { // per ogni arco del coalbero (e quindi vettore di supporto)
		for(int j = 0; j < m; j++) { // per ogni arco di G
			if(archiG[j] == archi_C[i]) {
				vettori_supporto[i][j] = 1; // pongo a 1 solo l'indice corrispondente all'arco del coalbero
			}
		}	
	}
	
	// vettore che conterrà la mia base di cicli fondamentali
	std::vector<std::vector<T>> cicli_fondamentali; 
	
	for(int i = 0; i < k; i++) {
		// --> i INDICIZZA IL VETTORE DI SUPPORTO SU CUI STO LAVORANDO 
		// ----------------------------------------------------------------------------------
		// TROVIAMO IL CICLO MINIMO IL CUI PRODOTTO SCALARE CON S_i È = 1 mod2 (booleano)
		// ----------------------------------------------------------------------------------
		
		// CREAZIONE GRAFO AUSILIARIO G' 
		undirected_graph<std::pair<T,int>> grafo_ausiliario; 
		// OSS: per convenzione u+ è la coppia (u,1) u- è la coppia (u,-1)
		// --> GESTISCO SEGNO ASSOCIATO AL NODO TRAMITE COPPIA
		
		for(int j = 0; j < m; j++) {
			// QUI j INDICIZZA L'ARCO (u,v) DI G ORIGINALE CHE STO CONSIDERANDO
			
			T u = archiG[j].from(); // estraggo nodi dell'arco
			T v = archiG[j].to();
			
			std::pair<T,int> u_più = {u,1}; // definisco i nuovi nodi di G'
			std::pair<T,int> u_meno = {u,-1};
			std::pair<T,int> v_più = {v,1};
			std::pair<T,int> v_meno = {v,-1};
			
			// arco j-esimo di G attivo nel vettore di supporto i-esimo
			if(vettori_supporto[i][j] == 1) {
				// archi incrociati se attivo
				grafo_ausiliario.add_edge(u_più, v_meno); 
				grafo_ausiliario.add_edge(u_meno, v_più); 
			}
			else {
				// archi paralleli se non attivo
				grafo_ausiliario.add_edge(u_più, v_più); 
				grafo_ausiliario.add_edge(u_meno, v_meno); 
			}
		}
		
		//CALCOLO CICLI POTENZIALI (cammini minimi)
		std::vector<std::vector<int>> cicli_potenziali(nodiG.size(), std::vector<int>(m, 0)); // inizializzo e definisco
		// vettore in cui salvo cicli potenziali in formato booleano (C_mu)
		
		std::vector<std::vector<T>> cammini_potenziali(nodiG.size()); // definisco e alloco lo spazio
		// vettore in cui salvo cicli potenziali effettivi su G (vettori sono di tipo T, non int)
		// OSS: ne trovo tanti quanti sono i nodi del grafo G
		
		for(int j = 0; j < n; j++) {
			// QUI j INDICIZZA NODO DI G ORIGINALE CHE STO CONSIDERANDO
			
			// calcolo cammino minimo tra v+ e v- per ogni v nodo di G
			std::vector<std::pair<T,int>> cammino; 
			// OSS: è un cammino di "coppie" perché viene fatto sul grafo ausiliario G'
			
			T v = nodiG[j]; // considero il nodo j-esimo da G (v)
			
			std::pair<T,int> v_più = {v,1}; // inizializzo i nodi corrispondenti in G' (v+ e v-)
			std::pair<T,int> v_meno = {v,-1};
			
			// trovo il grafo risultante da Dijkstra per trovare i cammini minimi
			undirected_graph<std::pair<T,int>> Dijkstra_grafo_ausiliario = Dijkstra(grafo_ausiliario, v_più);	
			
			// chiamo findpath per costruire il cammino
			std::set<std::pair<T,int>> visitati; 
			findpath(Dijkstra_grafo_ausiliario, v_più, v_meno, cammino, visitati);
			
			// trovato il cammino mi interessano soltanto i nodi (senza segno)
			// quindi alloco la memoria necessaria
			size_t len_cammino = cammino.size();
			cammini_potenziali[j].resize(len_cammino);
			
			// estraggo il cammino minimo e lo salvo nei cammini potenziali senza segno
			for(size_t c = 0; c < len_cammino; c++) {
				cammini_potenziali[j][c] = cammino[c].first;
			}
			
			// calcolo ciclo potenziale associato al cammino del nodo v (C_mu)
			std::vector<undirected_edge<T>> archi_cammino; // inizializzo
			archi_cammino.reserve(len_cammino); // alloco memoria
			
			for(size_t c = 0; c < len_cammino - 1; c++) {
				undirected_edge<T> edge(cammino[c].first, cammino[c+1].first); // costruisco gli archi associati al cammino
				archi_cammino.push_back(edge); // salvo gli archi
			}
			// creazione C_mu
			for(int h = 0; h < m; h ++) {
				//cammino lungo l -> abbiamo l-1 archi
				for(size_t c = 0; c < len_cammino - 1; c++) {
					if(archiG[h] == archi_cammino[c]) { // conto quante volte un arco di G è presente nel cammino (mod2)
						cicli_potenziali[j][h] = (cicli_potenziali[j][h] + 1) % 2; 
						//incremento di 1, e faccio modulo 2
					}
				}
			}
		}
		
		//prendiamo come ciclo fondamentale quello con meno elementi pari a 1
		std::vector<int> ciclo_minimo = cicli_potenziali[0]; // inizializzo il minimo come il primo
		std::vector<T> cammino_ciclo_minimo = cammini_potenziali[0];
		
		// funzione che conta le occorrenze di 1 in un vettore
		auto numero_minimo_uni = std::count(ciclo_minimo.begin(), ciclo_minimo.end(), 1); 
		
		// ciclo sul numero di nodi (ovvero di vettori di incidenza C_mu) di G
		for(int j = 1; j < n; j++) {
			// funzione che conta le occorrenze di 1 in un vettore
			auto numero_uni = std::count(cicli_potenziali[j].begin(), cicli_potenziali[j].end(), 1); 
			// cerco il vettore C_mu migliore e il corrispettivo ciclo in G
			if(numero_uni < numero_minimo_uni) {
				ciclo_minimo = cicli_potenziali[j]; // C_mu
				cammino_ciclo_minimo = cammini_potenziali[j]; // ciclo in G
				numero_minimo_uni = numero_uni; // numero di uni
			}
		}
		
		//----------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------
		cicli_fondamentali.push_back(cammino_ciclo_minimo); // aggiungo il ciclo fondamentale trovato associato al vettore di supporto i
		
		//aggiornamento vettori supporto successivi (pseudocodice)
		for(int j = i+1; j < k; j++) {
			if(prod_scalare_bool(ciclo_minimo, vettori_supporto[j]) == 1) {
				vettori_supporto[j] = differenza_simmetrica_bool(vettori_supporto[j], vettori_supporto[i]);
			}
		}
	}
	
	return cicli_fondamentali;
}	
