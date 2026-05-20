#include <iostream>
#include <Eigen/Dense>
#include "gradiente.hpp"

int main() {
	
	const double tol = 1.0e-15;
	unsigned int n = 20;

	Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
	
	if (abs(B.determinant()) < tol)
    return -1;

	Eigen::MatrixXd A = B.transpose() * B;
	Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);

	Eigen::VectorXd b = A * x_ex;

	Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
	
	const double res_tol = 1.0e-12;
	
	Eigen::VectorXd x = grad_con(A, b, x0, res_tol);
	
	double err_relativo = (x - x_ex).norm() / x_ex.norm();
	
	std::cout << "matrice A = " << A << "\n";
	std::cout << "soluzione esatta: \n" << x_ex << "\n";
	std::cout << "soluzione grad_con: \n" << x << "\n";
	std::cout << "errore relativo: " << err_relativo << std::endl;
	
	
}