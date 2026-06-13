#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include "undirected_graph.h"

// definiamo una mappa di vettori associati ad archi: per ogni arco abbiamo
// tipo = -1 se resistenza, tipo = +1 se generatore
// modulo = valore associato
// segno = +1 se morsetto positivo è il nodo più piccolo (il primo nell'arco), -1 altrimenti

using namespace std;
undirected_graph<int> lettura_file(string filename, map<undirected_edge<int>, vector<double>>& info) {
	
	// definizione grafo
	undirected_graph<int> circuito;
	
	// inizio lettura file
	ifstream ifs(filename);
	if ( ifs.is_open() ) { // se il file è stato aperto con successo
		while( !ifs.eof() ) {
			string tipo;
			double modulo;
			int nodoA; // primo che viene, non il più piccolo
			int nodoB;
			ifs >> tipo >> modulo >> nodoA >> nodoB; 
			
			// aggiungo l'arco al grafo circuito
			circuito.add_edge(nodoA, nodoB);
			
			// aggiungo informazioni alla mappa info
			undirected_edge<int> arco(nodoA, nodoB);
			
			vector<double> vec_info(4);
			if (tipo[0] == 'R') { // supponiamo che la netlist sia scritta come richiesto :D 
				vec_info[0] = -1; // tipo = -1 se resistenza
				vec_info[2] = +1; 
			}
			else {
				vec_info[0] = +1; // tipo = +1 se generatore
				if (nodoA <= nodoB) {
					vec_info[2] = +1; // morsetto positivo = primo nodo (+1)
				}
				else { // se nodoA > nodoB
					vec_info[2] = -1; // morsetto positivo = secondo nodo (-1)
				}
			}
			vec_info[1] = modulo; // salvo il modulo
			
			char n = tipo[1]; // salvo il numero di V o R
			stringstream ss;
			ss << n; // inserisco il carattere nel flusso
			double numero;
			ss >> numero; // lo estraggo come double
			vec_info[3] = numero; 
			
			info[arco] = vec_info;
		}
	}
	return circuito;
}
