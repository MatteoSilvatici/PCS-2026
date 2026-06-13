#include <iostream>
#include <Eigen/Dense>

Eigen::VectorXd grad_con(Eigen::MatrixXd A, Eigen::VectorXd b, Eigen::VectorXd x0, double res_tol) {
	
	// calcolo il residuo iniziale
	Eigen::VectorXd r = b - A * x0;
	
	// direzione di discesa iniziale
	Eigen::VectorXd p = r;
	
	// inizializzo lunghezza 
	double alpha = 0.0;
	
	// inizializzo valore beta
	double beta = 0.0;
	
	// inizializzo soluzione 
	Eigen::VectorXd x = x0;
	
	// scelgo itermax
	int itmax = 1000;
	int it = 0;
	
	// ciclo while del metodo del gradiente
	while (r.norm() > res_tol && it < itmax) {
		
		// calcolo lunghezza del passo
		alpha = (p.dot(r)) / (p.dot(A * p));
		
		// calcolo soluzione x al passo k+1
		x = x + alpha * p;
		
		// calcolo residuo passo k+1
		r = b - A * x;
		
		// calcolo beta passo k
		beta = (p.dot(A * r)) / (p.dot(A * p));
		
		// calcolo direzione successiva
		p = r - beta * p;
		
		// incremento iteratore
		it++;
		
	}
	
	return x;
	
}










