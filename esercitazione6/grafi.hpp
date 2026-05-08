#pragma once
#include <iostream>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

template<typename T>
class unidirected_edge {
	T from_; // nodo minore (partenza)
	T to_;   // nodo maggiore (arrivo)

public:
	// costruttore default
	unidirected_edge():
		from_{},
		to_{}
	{}

	// costruttore
	unidirected_edge(T u, T v) {
		from_ = std::min(u,v);
		to_ = std::max(u,v);
	}
	
	// per restituire i nodi
	T from() const {
		return from_;
	}
	T to() const {
		return to_;
	}
	
	// operatore confronto ordine
	bool operator<(const unidirected_edge& other) const {
		if (from_ < other.from_) {
			return true;
		}
		if (from_ == other.from_) {
			if (to_ < other.to_) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	
	// operatore confronto uguaglianza
	bool operator==(const unidirected_edge& other) const {
		if (from_ == other.from_ && to_ == other.to_) {
			return true;
		}
		else {
			return false;
		}
	}
	
	// operatore di stampa 
	friend std::ostream& operator<<(std::ostream& os, const unidirected_edge& arco) {
        os << "(" << arco.from_ << " -- " << arco.to_ << ")";
        return os;
	}
	// friend permette a std::cout di stampare un oggetto personalizzato
	// siccome cout non appartiene alla mia classe, deve essere un 'friend' per vedere i dati interni da stampare
};

template <typename T>
class unidirected_graph {
	// T = key (nodo), set<T> = insieme dei nodi adiacenti
	std::unordered_map<T, std::set<T>> mappa_adiacenza;
	// unordered map perchè ci permette di trovare gli adiacenti di un nodo in O(1) (tempo di calcolare l'hash)
	
	// edge = arco, int = id dell'arco
	std::map<unidirected_edge<T>, int> arco_to_id;
	// map perchè in questo modo le chiavi sono ordinabili 
	
	// int = id dell'arco, edge = arco
	std::map<int, unidirected_edge<T>> id_to_arco;
	// un'altra mappa per non dover scorrere tutta l'altra mappa per trovare l'arco
	
	// contatore numerico per contare gli archi (id)
	int next_id_arco;
	
public:
	// costruttore di default
	unidirected_graph() : 
		next_id_arco(0) 
	{}
	
	// costruttore di copia
	unidirected_graph(const unidirected_graph& other): // const perchè solo lettura
	
		// tutto ciò che c'è tra ":" e "{}" è la lista di inizializzazione
		mappa_adiacenza(other.mappa_adiacenza), // creo la mappa di adiacenza passando come modello l'altro grafo
		arco_to_id(other.arco_to_id), // e così via...
		id_to_arco(other.id_to_arco),
		next_id_arco(other.next_id_arco)	
		
	{} // se avessi messo tutto dentro le graffe avrei cresto le tre mappe vuote e solo dopo avrei
	   // copiato dentro i dati (più lento)
	
	// metodo neighbours()
	std::set<T> neighbours(T node) const{  // const perchè solo lettura
	
		// con find() cerco il nodo nella mappa -> restituisce un iteratore alla posizione trovata
		auto it = mappa_adiacenza.find(node); 
		// in questo caso "auto" sta per "std::map<T, std::set<T>>::const_iterator"
		
		// se la ricerca ha avuto successo ~ controllo se it è diverso da end()
		if (it != mappa_adiacenza.end()) {
			
			// nel caso it -> second contiene il valore associato (it -> first invece la chiave)
			return it->second;
		}
	
		// altrimenti se non è stato trovato il nodo, restituisco un insieme vuoto (no vicini)
		return std::set<T>();
	}
	
	// metodo add_edge()
	void add_edge(const unidirected_edge<T>& edge) {
		// mi occupo della mappa di adiacenza (estraggo i nodi)
		T u = edge.from();
		T v = edge.to();
		
		// inserisco quindi u nei vicini di v e viceversa (grafo non direzionato)
		mappa_adiacenza[u].insert(v);
		mappa_adiacenza[v].insert(u);
		// [] crea automaticamente il set vuoto se il nodo non era già nel grafo
		
		// mi occupo della numerazione degli archi
		if (arco_to_id.find(edge) == arco_to_id.end()) { // se restituisce end() l'arco è nuovo
			// assegno il prossimo valore del contatore al nuovo id
			int current_id = next_id_arco++;
			
			// salvo il collegamento nella mappa arco->id
			arco_to_id[edge] = current_id;
			
			// salvo anche nella mappa id->arco
			id_to_arco[current_id] = edge;
		}
	}
	
	// metodo all_edges()
	std::list<unidirected_edge<T>> all_edges() const {
		// creo la lista vuota
		std::list<unidirected_edge<T>> lista_archi;
		
		// scorro la mappa arco_to_id (ogni elemento è una coppia)
		for (const auto& coppia: arco_to_id) {
			// mi interessa coppia.first (arco)
			lista_archi.push_back(coppia.first);
		}
		
		// ritorno la lista completa
		return lista_archi;
	}
	
	// metodo all_nodes()
	std::set<T> all_nodes() const {
		// creo la lista vuota
		std::set<T> lista_nodi;
		
		// scorro la mappa di adiacenza
		for (const auto& coppia: mappa_adiacenza) {
			// mi interessa coppia.first (nodo)
			lista_nodi.insert(coppia.first);
			// per i set si usa insert(), per le liste push_back()
		}
		
		// ritorno il set completo
		return lista_nodi;
	}
	
	// metodo edge_number()
	int edge_number(const unidirected_edge<T>& edge) const {
		// cerco l'arco nella mappa arco->id
		auto it = arco_to_id.find(edge);
		
		// se lo trovo restituisco il suo valore (it->second)
		if (it != arco_to_id.end()) {
			return it->second;
		}
		
		// se non lo trovo restituisco 'errore' (-1)
		return -1;
	}
	
	// metodo edge_at()
	unidirected_edge<T> edge_at(int id) const {
		// .at() cerca la chiave (id), se la trova restituisce l'arco, altrimenti lancia un'eccezione
		return id_to_arco.at(id);
	}
	
	//operator-() differenza (G - G')
	unidirected_graph<T> operator-(const unidirected_graph<T>& other) const {
		// creo il grafo che conterrà il risultato della differenza
		unidirected_graph<T> diff;
		
		// con all_edges() prendiamo la lista di tutti gli archi del grafico G
		std::list<unidirected_edge<T>> archi_G = this->all_edges();
		
		// studiamo arco per arco
		for (const auto& arco: archi_G) {
			//vediamo se l'arco in considerazione è presente nel grafo G'
			auto it = other.arco_to_id.find(arco);
			
			// se non è presente lo teniamo nell risultato diff
			if (it == other.arco_to_id.end()) {
				diff.add_edge(arco);
			}
		}
		
		// retituisco il grafo G - G' (diff)
		return diff;
	}
	
};