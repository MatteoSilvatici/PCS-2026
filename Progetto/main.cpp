#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "undirected_graph.h"
#include "coda_pila.h"
#include "cicli_fondamentali.h"
#include "algoritmi_visita.h"
#include "input_stream.h"
#include "sistema_lineare.h"
#include <Eigen/Dense>

using namespace std;

int main() {
	
	string filename = "netlist.txt";
	map<undirected_edge<int>, vector<double>> info;
	undirected_graph<int> circuito = lettura_file(filename, info);
	
	// estraggo il numero di resistori nel circuito
	int m = 0;
	for (auto& itor : info) { // cerco nella mappa info tutti i resistori
		if (itor.second[0] == -1) {
			m++;
		}
	}
	
	Eigen::VectorXd vr_depina = tensioni_DePina(info, circuito);
	
	vector<double> Ir_depina(m);
	for (auto const& [arco, dati] : info) {
		if (dati[0] == -1) {
			int i = dati[3];
			double corrente = vr_depina[i-1] / dati[1]; // V = RI --> I = V / R
			Ir_depina[i-1] = corrente;
		}
	}


	cout << "--------------------------------------------\n";
	cout << "RISULTATI FINALI DEPINA (Tensioni e correnti ai capi dei resistori):\n";
	cout << "--------------------------------------------\n";

	for (auto const& [arco, dati] : info) {	
		// Il codice tipo dei resistori è -1
		if (dati[0] == -1) { 
			cout << "Resistore R" << dati[3] 
				<< " [Arco " << arco.from() << " -> " << arco.to() << "]: V = "
				<< vr_depina[dati[3]-1] << " volts, I = " << Ir_depina[dati[3]-1] << " amps.\n";
        

		}
	}
	cout << "--------------------------------------------\n";
	
	Eigen::VectorXd vr_dfs = tensioni_DFS(info, circuito);
	
	vector<double> Ir_dfs(m);
	for (auto const& [arco, dati] : info) {
		if (dati[0] == -1) {
			int i = dati[3];
			double corrente = vr_dfs[i-1] / dati[1]; // V = RI --> I = V / R
			Ir_dfs[i-1] = corrente;
		}
	}

	cout << "--------------------------------------------\n";
	cout << "RISULTATI FINALI DFS (Tensioni e correnti ai capi dei resistori):\n";
	cout << "--------------------------------------------\n";

	for (auto const& [arco, dati] : info) {	
		// Il codice tipo dei resistori è -1
		if (dati[0] == -1) { 
			cout << "Resistore R" << dati[3] 
				<< " [Arco " << arco.from() << " -> " << arco.to() << "]: V = "
				<< vr_dfs[dati[3]-1] << " volts, I = " << Ir_dfs[dati[3]-1] << " amps.\n";
        

		}
	}
	cout << "--------------------------------------------\n";
	
	
    return 0;
}


