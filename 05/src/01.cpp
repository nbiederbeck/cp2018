// vim: commentstring=//%s
// Aufgabe 1: Diagonalisierung per Hand
#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

using std::cout;
using std::endl;


using namespace Eigen;
using Eigen::EigenSolver;
using Eigen::MatrixXd;

void eigen_solve(MatrixXd M);
void save_eigenvalues(MatrixXcd ev, const char *filename);
void get_Q(MatrixXd M);


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

    cout << "Output first vector/column in Matrix" << endl;
    cout << M.col(1)(1) << endl;

    get_Q(M);

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

void get_vector (MatrixXd M){
    /* v_i = a_i + alpha * einheitsvektor */

}

void get_unit_matrix(MatrixXd M){
    /* Take size of M and define unit matrix */


}



void get_Q (MatrixXd M){
    /*Q = I - (2*v*v^T / (v^T*v)) */
    cout << "Output first vector/column in Matrix" << endl;
    cout << M.col(0) << endl;


    /* Get first column of matrix as vector */
    VectorXd vec =  M.col(0);

    /* Calculate alpha */
    double alpha = std::copysign(1, M.col(0)(0))*vec.norm();

    cout <<"Norm of vector" << endl;
    cout << alpha << endl;

    /* Get vector_i from v_i = a_i + alpha * einheitsvektor */

    VectorXd vec_2 = vec + alpha*


}

void get_alpha (MatrixXd M){
    /* alpha = sign(a_11)* || a_1 || */

}






