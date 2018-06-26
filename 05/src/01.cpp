// vim: commentstring=//%s
// Aufgabe 1: Diagonalisierung per Hand
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>

using std::cout;
using std::endl;
using std::copysign;
using std::pow;
using std::sqrt;

// using namespace Eigen;
using Eigen::EigenSolver;
using Eigen::MatrixXd;
using Eigen::MatrixXcd;
using Eigen::VectorXd;

void eigen_solve(MatrixXd M);
void save_matrices_to_file(MatrixXcd ev, const char *filename);

MatrixXd prune_matrix(MatrixXd M, double eps = 1e-15) {
    const int dim = M.rows();
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            if (abs(M(i, j)) < eps) {
                M(i, j) = 0;
            }
        }
    }
    return M;
}

<<<<<<< HEAD

=======
>>>>>>> maxi
MatrixXd householder(MatrixXd M) {
    cout << "Householder Algorithm: " << endl;
    cout << "====================================" << endl << endl;

    VectorXd a;
    double alpha;
    double r;
    const int dim = M.rows();
    VectorXd v(dim);


    // Folge Wikipedia Anleitung:
    // https://en.wikipedia.org/wiki/Householder_transformation#Examples
    for(int a_row = 0; a_row < dim - 2; a_row++) {
        a = M.row(a_row);
        alpha = -1.0 * copysign(a.tail(dim - a_row - 1).norm(), a(a_row + 1));
        r = std::sqrt(0.5 * (std::pow(alpha, 2) - a(a_row + 1) * alpha));
<<<<<<< HEAD

=======
>>>>>>> maxi
        v(a_row) = 0.;
        v(a_row + 1) = (a(a_row + 1) - alpha) / (2 * r);

        for(int i = a_row + 2; i < dim; i++) {
            v(i) = a(i) / (2 * r);
        }

        MatrixXd P = MatrixXd::Zero(dim, dim);
        P.diagonal() = MatrixXd::Ones(dim, 1);

        P -= 2 * v * v.transpose();
        M = P.transpose() * M * P;

    }

    // cout << "Tridiagonalematrix nach Householder-Algorithmus:" << endl;
    // cout << M << endl;

    return prune_matrix(M);
}

MatrixXd jacobi_rotation(MatrixXd M) {
    const int dim = M.rows();
    const double eps = 1e-16;
    int q;
    double theta, t, c, s;
    int jacobicounter = 0;

    while (((M.cwiseProduct(M)).sum() - (M.cwiseProduct(M)).trace()) > eps) {
        ++jacobicounter;
        for (int p = 0; p < dim; ++p) {
            for (int q = 0; q < dim; ++q) {
                if (p == q) {
                    break;
                }
                theta = (M(q, q) - M(p, p)) / (2.0 * M(p, q));

                t = copysign(1.0, theta) / (abs(theta) + sqrt(pow(theta, 2.0) + 1.0));
                c = 1.0 / sqrt(1.0 + pow(t, 2.0));
                s = t * c;

                MatrixXd P = MatrixXd::Zero(dim, dim);
                P.diagonal() = MatrixXd::Ones(dim, 1);
                P(p, p) = c;
                P(q, q) = c;
                P(p, q) = s;
                P(q, p) = -s;

                M = P.transpose() * M * P;
            }
        }
    }
    cout << "# of Jacobi-Rotations ('Sweeps'): " << jacobicounter << endl;
    return prune_matrix(M);
}

int main(int argc, char *argv[])
{
    cout << "====================================" << endl;
    cout << "Aufgabe 1: Diagonalisierung per Hand" << endl;
    cout << "====================================" << endl << endl;

    MatrixXd M, H, J_M, J_H;

    int N = 5;
    M = MatrixXd::Constant(N, N, 1.0);
    MatrixXd d(N,1);
    d << 1, 2, 3, 4, 5;
    M.diagonal() = d;

    cout << "M = " << endl;
    cout << M << endl << endl;

    // Aufgabenteil (b)
    eigen_solve(M);

    // Aufgabenteil (a)
    H = householder(M);
    cout << "H = " << endl;
    cout << H << endl << endl;
    save_matrices_to_file(H, "build/householder.txt");

    cout << "H: ";
    J_H = jacobi_rotation(H);
    cout << "J_H = " << endl;
    cout << J_H << endl << endl;
    save_matrices_to_file(J_H.diagonal(), "build/hand_eigenvalues.txt");

    cout << "M: ";
    J_M = jacobi_rotation(H);
    cout << "J_M = " << endl;
    cout << J_M << endl << endl;

    return 0;
}


void eigen_solve(MatrixXd M) {
    EigenSolver<MatrixXd> es(M);

    MatrixXcd ev = es.eigenvalues();

    cout << "Eigenwerte der Matrix M, geloest durch Eigen::EigenSolver" << endl;
    cout << ev << endl << endl;

    save_matrices_to_file(ev, "build/eigensolver_eigenvalues.txt");
}

void save_matrices_to_file(MatrixXcd ev, const char *filename) {
    std::ofstream file (filename);
    file << ev << endl;
}
