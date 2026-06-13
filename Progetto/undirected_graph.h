#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

// CLASSE RAPPRESENTA ARCO
template<typename T>
class undirected_edge {
	// arco non diretto caratterizzato unicamente dai due nodi che collega (unici attributi)
	T nodeA;
	T nodeB;
	
	public:
		undirected_edge(T i, T j) { // costruttore user_defined -> arco tra nodi i e j
			if (i <= j) { // permessi anche archi da un nodo in sè stesso
				nodeA = i; 
				nodeB = j; 	
			}
			else { 
				nodeA = j; 
				nodeB = i; 
			}
		}
		
		// metodi from e to per ricavare nodi dell'arco
		const T& from() const {
			return nodeA;
		}
		
		const T& to() const {
			return nodeB; 
		}
		
		// operatore < (ordine lessicografico)
		bool operator<(const undirected_edge& other) const{
			if ((nodeA < other.nodeA) || ( (nodeA == other.nodeA) && (nodeB < other.nodeB))) {
				return true;
			}
			else {
				return false;
			}
		}
		
		// operatore confronto uguaglianza 
		bool operator==(const undirected_edge& other) const{
			if (nodeA == other.nodeA && (nodeB == other.nodeB)) {
				return true; 
			}
			else {
				return false; 
			}
		}
};

// operatore di stampa a terminale
template<typename T>
std::ostream& operator<<(std::ostream& os, const undirected_edge<T>& edge) {
// OSS: qui nell'input della funzione devo specificare <T> -> siamo fuori dalla classe
	os << "(" << edge.from() << "," << edge.to() << ")";
	return os; 
}

// CLASSE RAPPRESENTA GRAFO 

template<typename T> 
class undirected_graph {
	std::map<T, std::set<T>> mappa_adiacenza; 
	// per ogni nodo salvo insieme dei vicini -> uso set perché non voglio duplicati
	
	// vettore contenitore di tutti gli archi del grafo
	std::vector<undirected_edge<T>> vettore_archi; 
	
	public:
	// costruttore default -> inizializza mappa adiacenza vuota
	undirected_graph() {}
	
	// costruttore di copia
	undirected_graph(const undirected_graph& other) {
		mappa_adiacenza = other.mappa_adiacenza; 
		vettore_archi = other.vettore_archi;
	}
	
	// metodo neighbours (nodi adiacenti)
	const std::set<T>& neighbours(const T& node) const {
		auto itor = mappa_adiacenza.find(node);
		// OSS: find restituisce un iteratore. Se non trova il nodo, esce dalla mappa (quello che trovo con .end())
		
		if (itor == mappa_adiacenza.end()) {
			static const std::set<T> set_vuoto; //aggiungo static -> altrimenti 
			//set_vuoto eliminato quando termina funzione, ma voglio restituire
			//riferimento per evitare copie 
			return set_vuoto; //ritorna set vuoto se nodo non trovato
		}
		
		return itor->second; // secoond permette accedere al secondo elemento della coppia
		//(chiave,valore) a cui puntava l'iteratore
		
	}
	
	void add_edge(T i, T j) {
		undirected_edge<T> edge(i,j); // creo arco -> classe definita sopra
		
		// conto quante volte è presente il nodo j nel set di adiacenza di i (1 o 0)
		if (mappa_adiacenza[i].count(j) == 0) { // se arco non ancora presente 
		
			// aggiorno lista adiacenza
			mappa_adiacenza[i].insert(j);
			mappa_adiacenza[j].insert(i);
			// uso operatore [] di std::map -> voglio poter creare nuovo nodo se non già presente
			// metodo insert -> aggiungere elemento al set dei vicini
			
			// aggiungo il nuovo arco al vettore degli archi del grafo
			vettore_archi.push_back(edge);
		}
		
		std::sort(vettore_archi.begin(), vettore_archi.end()); // ordino vettore degli archi 
		// rispetto ordinamento della classe undirected_edge
	}
	
	// metodo che restituisce tutti gli archi di un grafo
	const std::vector<undirected_edge<T>>& all_edges() const {
		return vettore_archi;
	}
	
	// metodo che restituisce tutti i nodi del grafo
	std::vector<T> all_nodes() const { // vector è rapido per inserire elementi
		
		// inizializzo vettore nodi
		std::vector<T> nodes;
		
		// OSS: oggetto nodes costruito dentro la funzione -> non posso restituire
		// riferimento, perché distrutto quando funzione termina, alternativa
		// sarebbe usare static e set come sopra, ma vector più rapido per inserire 
		// elementi: unico scopo di questo metodo
		
		// itero sui nodi nella mappa di adiacenza
		for (const auto& itor : mappa_adiacenza) {
			
			// aggiugno ogni nodo al vettore nodes
			nodes.push_back(itor.first); 
			
			// OSS: nel range_based for, itor è proprio il riferimento 
			// ad un elemento della mappa, non un puntatore da dereferenziare
			// (non posso usare l'operatore ->)
		}
		return nodes; 
	}
	
	// metodo che restituisce la posizione dell'arco nel vettore degli archi (partendo da 1)
	int edge_number(const undirected_edge<T>& edge) const {
		
		// ricavo la grandezza del vettore degli archi
		int size = vettore_archi.size();
		
		// per ogni arco cerco la sua posizione nel vettore degli archi (O(n))
		for (int i = 0; i < size; i++) {
			if (vettore_archi[i] == edge) {
				return i+1;
			}
		}
		
		return -1; // restituisce -1 se arco non trovato
	}
	
	// restituisce l'arco in posizione i-esima nel vettore degli archi
	const undirected_edge<T>& edge_at(size_t i) {
		
		// se i appartiene al range accettabile
		if ((i > 0) && (i <= vettore_archi.size())) {
			return vettore_archi[i-1]; // il primo elemento ha indice 1
		}
		
		return vettore_archi[0]; // se richiesto arco non esistente, restituisco
		// primo arco, suppongo che metodo chiamato con vettore_archi non vuoto
		// (questo caso non è rilevante per il progetto)
	}
	
	// operatore differenza tra grafi G - G'
	undirected_graph<T> operator-(const undirected_graph& other) const{
		
		// definisco il grafo risultante dalla differenza
		undirected_graph<T> grafo_differenza; 
		
		// ciclo sul numero di archi del grafo di partenza G
		for(size_t i = 0; i < vettore_archi.size(); i++) {
			
			// inizializzo variabile ausiliare 
			bool presente_entrambi = false; 
			
			// ciclo sul numero di archi del grafo G'
			for (size_t j = 0; j < other.vettore_archi.size(); j++) {
				
				// controllo 
				if (vettore_archi[i] == other.vettore_archi[j]) {
					presente_entrambi = true;
				}
			}
			
			// se non è presente in G', lo aggiungo al grafo risultante
			if (! presente_entrambi) {
				grafo_differenza.add_edge(vettore_archi[i].from(), vettore_archi[i].to());
			}
		}
		
		return grafo_differenza;
	}
};