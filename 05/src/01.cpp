// vim: commentstring=//%s
// Aufgabe 1: Diagonalisierung per Hand
#include <iostream>
#include <fstream>
#include <Eigen/Dense>

using std::cout;
using std::endl;

using namespace Eigen;
using Eigen::EigenSolver;
using Eigen::MatrixXd;

void eigen_solve(MatrixXd M);
void save_eigenvalues(MatrixXcd ev, const char *filename);

int main(int argc, char *argv[])
{
    cout << "====================================" << endl;
    cout << "Aufgabe 1: Diagonalisierung per Hand" << endl;
    cout << "====================================" << endl << endl;

    // Define Test Matrix
	int N = 5;
	MatrixXd M = MatrixXd::Constant(N, N, 1.0);
	MatrixXd d(N,1);
	d << 1, 2, 3, 4, 5;

	M.diagonal() = d;
    cout << M << endl;

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
