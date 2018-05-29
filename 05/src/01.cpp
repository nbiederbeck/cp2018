// vim: commentstring=//%s
// Aufgabe 1: Diagonalisierung per Hand
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>

using std::cout;
using std::endl;
using std::signbit;

using namespace Eigen;
using Eigen::EigenSolver;
using Eigen::MatrixXd;
using Eigen::VectorXd;

void eigen_solve(MatrixXd M);
void save_eigenvalues(MatrixXcd ev, const char *filename);
void householder(MatrixXd M) {
		cout << "Householder Algorithm: " << endl;
		cout << "====================================" << endl << endl;

		VectorXd a;
		int act_row; double alpha;
		double r;
		int dim = M.rows();
		VectorXd v(dim);

		MatrixXd P(dim, dim);

		act_row = 0;
		a = M.row(act_row);
		if(signbit(a(act_row+1)) != 0){
				alpha = std::sqrt(a.tail(dim-act_row-1).squaredNorm());
		}
		else{
				alpha = -1.0 * sqrt(a.tail(dim-act_row-1).squaredNorm());
		};
		r = std::sqrt(0.5*(std::pow(alpha, 2)-a(act_row+1)*alpha));
		v(0) = 0.;
		v(1) = (a(act_row+1) - alpha)/(2*r);
		for(int i=2; i<dim; i++){
				v(i) = a(i)/(2*r);
		}
		
		P.diagonal() = MatrixXd::Ones(dim, 1);
		P -= 2*v*v.transpose();
		M = P.transpose()*M*P;

		std::cout <<  "alpha:" << alpha << std::endl;
		std::cout <<  "r:" << r << std::endl;
		std::cout <<  "v:" << v << std::endl;
		std::cout <<  "P:" << P << std::endl;
		std::cout <<  "M:" << M << std::endl;
}

int main(int argc, char *argv[])
{
		cout << "====================================" << endl;
		cout << "Aufgabe 1: Diagonalisierung per Hand" << endl;
		cout << "====================================" << endl << endl;

		// Define Test Matrix
		int N = 4;
		MatrixXd M = MatrixXd::Constant(N, N, 1.0);
		// MatrixXd d(N,1);
		// d << 2, 2, 3, 4, 5;

		M << 4, 1, -2, 2, 1, 2, 0, 1, -2, 0, 3, -2, 2, 1, -2, -1;

		// M.diagonal() = d;
		cout << M << endl;

		householder(M);

		eigen_solve(M);

		return 0;
}


void eigen_solve(MatrixXd M) {
		EigenSolver<MatrixXd> es(M);

		MatrixXcd ev = es.eigenvalues();

		cout << "Eigenwerte der Matrix M, geloest durch Eigen::EigenSolver" << endl;
		cout << ev << endl;

		save_eigenvalues(ev, "build/eigensolver_eigenvalues.txt");
		save_eigenvalues(ev, "build/hand_eigenvalues.txt");
}

void save_eigenvalues(MatrixXcd ev, const char *filename) {
		std::ofstream file (filename);
		file << ev << endl;
}
