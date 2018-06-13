// vim: commentstring=//%s expandtab shiftwidth=4
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>


using std::cout;
using std::endl;


// generates hermitian matrix for cleaner code from worksheet
Eigen::MatrixXd generate_matrix() {
    Eigen::MatrixXd M(6, 6);
    M << 9, 10,  -7, 15,  13, 14,
      10,  1,   7, 15,   6, 11,
      -7,  7,  17,  3, -16, -4,
      15, 15,   3, -4,   7,  9,
      13,  6, -16,  7,  11, 16,
      14, 11,  -4,  9,  16,  8;
    return M;
}


// implementation of lanczos routine
Eigen::MatrixXd lanczos(Eigen::MatrixXd M, Eigen::VectorXd q) {
    return M;
}


Eigen::MatrixXd qr_iteration(Eigen::MatrixXd M) {
    return M;
}


void a() {
    Eigen::MatrixXd M = generate_matrix();

    Eigen::VectorXd q0(6);
    Eigen::VectorXd q1(6);
    q0 << 1, 1, 1, 1, 1, 1;
    q1 << 1, 2, 3, 4, 5, 6;

    Eigen::MatrixXd L0= lanczos(M, q0);
    Eigen::MatrixXd L1= lanczos(M, q1);

    cout << "Matrizes after Lanczos routine" << endl << endl
        << L0 << endl << endl
        << L1 << endl << endl;
}


void b() {
    Eigen::MatrixXd M = generate_matrix();

    Eigen::MatrixXd QR = qr_iteration(M);
    Eigen::EigenSolver<Eigen::MatrixXd> ES(M);
    Eigen::MatrixXcd EV = ES.eigenvalues().real();

    cout << "Eigenvalues of matrizes solved with QR-iteration / Eigen::EigenSolver" << endl << endl
        << QR << endl << endl
        << EV << endl << endl;
}


void c() {
    for (int N = 3; N <= 20; N++) {
        Eigen::MatrixXd RM(N, N);
        for (int i = 1; i <= 50; i++) {
        }
    }
}


int main() {
    cout << "Task 1" << endl << "======" << endl << endl
         << "(a)" << endl << "---" << endl << endl;
    a();
    cout << "(b)" << endl << "---" << endl << endl;
    b();
    cout << "(c)" << endl << "---" << endl << endl;
    c();
    return 0;
}
