#pragma once
#include <iostream>
#include <fstream>
#include "undirected_graph.h"
#include "coda_pila.h"
#include "cicli_fondamentali.h"
#include "algoritmi_visita.h"
#include "input_stream.h"
#include "gradiente.h"
#include <Eigen/Dense>

// caso con DFS
Eigen::VectorXd tensioni_DFS (const map<undirected_edge<int>, vector<double>>& info, const undirected_graph<int>& circuito) {
	
	std::vector<std::vector<int>> cicli_fond_DFS = DFS_cicli(circuito);
	
	// estraggo m e n
	int m = 0;
	for (auto& itor : info) { // cerco nella mappa info tutti i resistori
		if (itor.second[0] == -1) {
			m++;
		}
	}
	int n = cicli_fond_DFS.size();
	
	// creazione matrice B e vettore v
	Eigen::MatrixXd B = Eigen::MatrixXd::Zero(m, n);
	Eigen::VectorXd v = Eigen::VectorXd::Zero(n);
	for (int j = 0; j < n; j++) { // ciclo sulle maglie
		
		// estraggo la lunghezza del ciclo minimo
		int l = cicli_fond_DFS[j].size();
		for (int k = 0; k < l - 1; k++) { // ciclo sugli archi della maglia j
			int nodoA = cicli_fond_DFS[j][k]; // estraggo i nodi del cammino a due a due 
			int nodoB = cicli_fond_DFS[j][k+1];
			undirected_edge<int> arco(nodoA, nodoB);
			if (info.at(arco)[0] == -1) { // se arco contiene resistore 
				int i = info.at(arco)[3]; // ricavo il numero del resistore i
				if (nodoA <= nodoB) { // se verso percorrenza maglia = verso resistore 	
					B(i-1,j) = 1.0;
				}
				else { // altrimenti
					B(i-1,j) = -1.0;
				}
			}
			// per ogni maglia sommiamo i generatori di tensione
			else { // se arco contiene generatore
				if (info.at(arco)[2] == +1) { // nodo minore tra A e B = morsetto positivo
					if (nodoA <= nodoB) { // nodo A minore di B
						v[j] -= info.at(arco)[1]; // modulo con segno - (attraverso da + a -)
					}
					else {
						v[j] += info.at(arco)[1]; // modulo con segno + (attraverso da - a +)
					}
				}
				else { // nodo maggiore tra A e B = morsetto positivo
					if (nodoA <= nodoB) { // nodo A minore di B
						v[j] += info.at(arco)[1]; // modulo con segno + (attraverso da - a +)
					}
					else {
						v[j] -= info.at(arco)[1]; // modulo con segno - (attraverso da + a -)
					}
				}
			}
		}
	}
	
	// creazione matrice R
	Eigen::MatrixXd R = Eigen::MatrixXd::Zero(m,m);
	for (auto& itor : info) {
		if (itor.second[0] == -1) {
			int i = itor.second[3]; // numero resistore
			R(i-1,i-1) = itor.second[1]; // modulo
		}
	}
	
	// risolviamo il sistema B'RBi=v (dimensione: (n,m)*(m,m)*(m,n)*n = n)
	Eigen::MatrixXd A = (B.transpose() * R) * B; // calcolo matrice B'RBi
	Eigen::VectorXd i0 = Eigen::VectorXd::Zero(n); // soluzione iniziale (vettore di dimensione n: una corrente per ciclo)
	double res_tol = 1e-10; // tolleranza residuo
	
	Eigen::VectorXd i = grad_con(A, v, i0, res_tol); // uso il metodo del gradiente coniugato
	
	// calcolo tensioni relative ai resistori
	Eigen::VectorXd vr = Eigen::VectorXd::Zero(m);
	vr = (R * B) * i; 
	
	return vr;
}

// Caso con De Pina
Eigen::VectorXd tensioni_DePina (const map<undirected_edge<int>, vector<double>>& info, const undirected_graph<int>& circuito) {
	
	std::vector<std::vector<int>> cicli_min_DePina = DePina_cicli(circuito);
	
	// estraggo m e n
	int m = 0;
	for (auto& itor : info) { // cerco nella mappa info tutti i resistori
		if (itor.second[0] == -1) {
			m++;
		}
	}
	int n = cicli_min_DePina.size();
	
	// creazione matrice B e vettore v
	Eigen::MatrixXd B = Eigen::MatrixXd::Zero(m, n);
	Eigen::VectorXd v = Eigen::VectorXd::Zero(n);
	for (int j = 0; j < n; j++) { // ciclo sulle maglie
		
		// estraggo la lunghezza del ciclo minimo
		int l = cicli_min_DePina[j].size();
		for (int k = 0; k < l - 1; k++) { // ciclo sugli archi della maglia j
			int nodoA = cicli_min_DePina[j][k]; // estraggo i nodi del cammino a due a due 
			int nodoB = cicli_min_DePina[j][k+1];
			undirected_edge<int> arco(nodoA, nodoB);
			if (info.at(arco)[0] == -1) { // se arco contiene resistore 
				int i = info.at(arco)[3]; // ricavo il numero del resistore i
				if (nodoA <= nodoB) { // se verso percorrenza maglia = verso resistore 	
					B(i-1,j) = 1.0;
				}
				else { // altrimenti
					B(i-1,j) = -1.0;
				}
			}
			// per ogni maglia sommiamo i generatori di tensione
			else { // se arco contiene generatore
				if (info.at(arco)[2] == +1) { // nodo minore tra A e B = morsetto positivo
					if (nodoA <= nodoB) { // nodo A minore di B
						v[j] -= info.at(arco)[1]; // modulo con segno - (attraverso da + a -)
					}
					else {
						v[j] += info.at(arco)[1]; // modulo con segno + (attraverso da - a +)
					}
				}
				else { // nodo maggiore tra A e B = morsetto positivo
					if (nodoA <= nodoB) { // nodo A minore di B
						v[j] += info.at(arco)[1]; // modulo con segno + (attraverso da - a +)
					}
					else {
						v[j] -= info.at(arco)[1]; // modulo con segno - (attraverso da + a -)
					}
				}
			}
		}
	}
	
	// creazione matrice R
	Eigen::MatrixXd R = Eigen::MatrixXd::Zero(m,m);
	for (auto& itor : info) {
		if (itor.second[0] == -1) {
			int i = itor.second[3]; // numero resistore
			R(i-1,i-1) = itor.second[1]; // modulo
		}
	}
	
	// risolviamo il sistema B'RBi=v (dimensione: (n,m)*(m,m)*(m,n)*n = n) con n = numero cicli fond
	Eigen::MatrixXd A = (B.transpose() * R) * B; // calcolo matrice B'RBi (cc O((n+m)^3))
	Eigen::VectorXd i0 = Eigen::VectorXd::Zero(n); // soluzione iniziale (vettore di dimensione n: una corrente per ciclo)
	double res_tol = 1e-10; // tolleranza residuo
	
	Eigen::VectorXd i = grad_con(A, v, i0, res_tol); // uso il metodo del gradiente coniugato (cc O(k*n^2))
	
	// calcolo tensioni relative ai resistori
	Eigen::VectorXd vr = Eigen::VectorXd::Zero(m);
	vr = (R * B) * i; 
	
	return vr;
}