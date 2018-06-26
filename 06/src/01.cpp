// vim: commentstring=//%s expandtab shiftwidth=4
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>
#include <ctime>


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
Eigen::MatrixXd lanczos(Eigen::MatrixXd A, Eigen::VectorXd q) {

    Eigen::MatrixXd T = Eigen::MatrixXd::Zero(A.rows(), A.cols());

    // first normalize q vector
    Eigen::VectorXd temp = q.normalized();
    q = temp;  // q_1

    // calculate alpha and beta
    double alpha = q.transpose() * A * q; // alpha_1
    Eigen::VectorXd beta_q = A * q - alpha * q;  // beta_2 * q_2

    double beta = beta_q.norm();  // beta_2
    Eigen::VectorXd q_neu = beta_q / beta;  // q_2

    // manually set values from first "iteration"
    T(0, 0) = alpha;
    T(1, 0) = beta;
    T(0, 1) = beta;

    for (int i = 1; i < A.rows(); i++) {
        // alpha_2 = q_2.transpose * A * q_2
        alpha = q_neu.transpose() * A * q_neu;
        // beta_3 * q_3 = A * q_2 - alpha_2 * q_2 - beta_2 * q_1
        beta_q = A * q_neu - alpha * q_neu - beta * q;
        // beta_3
        beta = beta_q.norm();
        // q_3
        q_neu = beta_q / beta;

        // fill tridiagonalmatrix with values alpha and beta
        T(i, i) = alpha;
        if (i + 1 < A.rows()) {
            T(i, i+1) = beta;
            T(i+1, i) = beta;
        }
    }

    return T;
}


Eigen::MatrixXd qr_iteration(Eigen::MatrixXd A, Eigen::MatrixXd T) {
    // QR von Eigen, sorry
    Eigen::HouseholderQR<Eigen::MatrixXd> hqr(A.rows(), A.cols());

    Eigen::MatrixXd Q;

    Eigen::MatrixXd temp = A;

    double eps = 1e2;

    while (((A.cwiseProduct(A)).sum() - (A.cwiseProduct(A)).trace()) > eps) {
    // for (int i = 0; i < 5; i++) {
        hqr.compute(temp);
        Q = hqr.householderQ();
        A = Q.transpose() * temp * Q;
        temp = A;
    }
    return A;
}


// copied from sheet 5 task 1
Eigen::MatrixXd householder(Eigen::MatrixXd M) {
    Eigen::VectorXd a;
    double alpha;
    double r;
    const int dim = M.rows();
    Eigen::VectorXd v(dim);
    for (int a_row = 0; a_row < dim - 2; a_row++) {
        a = M.row(a_row);
        alpha = -1.0 * copysign(a.tail(dim - a_row - 1).norm(), a(a_row + 1));
        r = std::sqrt(0.5 * (std::pow(alpha, 2) - a(a_row + 1) * alpha));
        v(a_row) = 0.;
        v(a_row + 1) = (a(a_row + 1) - alpha) / (2 * r);
        for (int i = a_row + 2; i < dim; i++) {
            v(i) = a(i) / (2 * r);
        }
        Eigen::MatrixXd P = Eigen::MatrixXd::Zero(dim, dim);
        P.diagonal() = Eigen::MatrixXd::Ones(dim, 1);
        P -= 2 * v * v.transpose();
        M = P.transpose() * M * P;
    }
    return M;
}


void save_matrix_to_file(Eigen::MatrixXd M, const char *filename) {
    std::ofstream file (filename);
    file << M << endl;
}


void a() {
    Eigen::MatrixXd M = generate_matrix();

    Eigen::VectorXd q0(6);
    Eigen::VectorXd q1(6);
    q0 << 1, 1, 1, 1, 1, 1;
    q1 << 1, 2, 3, 4, 5, 6;
    q1 << 1, 0, 0, 0, 0, 0;

    Eigen::MatrixXd L0= lanczos(M, q0);
    Eigen::MatrixXd L1= lanczos(M, q1);

    cout << "Matrizes after Lanczos routine" << endl << endl
        << L0 << endl << endl
        << L1 << endl << endl;

    save_matrix_to_file(L0, "build/T0_cpp.tex");
    save_matrix_to_file(q0, "build/q0_cpp.tex");
    save_matrix_to_file(L1, "build/T1_cpp.tex");
    save_matrix_to_file(q1, "build/q1_cpp.tex");
}


void b() {
    Eigen::MatrixXd M = generate_matrix();

    Eigen::VectorXd q(6);
    q << 1, 1, 1, 1, 1, 1;
    Eigen::MatrixXd T = lanczos(M, q);

    Eigen::MatrixXd QR = qr_iteration(M, T);
    cout << QR << endl;
    Eigen::EigenSolver<Eigen::MatrixXd> ES(M);
    Eigen::MatrixXd EV = ES.eigenvalues().real();

    std::ofstream file ("build/task1b.txt");

    cout << "# Eigenvalues of matrizes solved with QR-iteration / Eigen::EigenSolver" << endl << endl
        << QR.diagonal() << endl << endl
        << EV << endl << endl;
    file << "# Eigenvalues of matrizes solved with QR-iteration / Eigen::EigenSolver" << endl
         << QR.diagonal() << endl << EV << endl;
}


void c() {
    Eigen::MatrixXd Lanczos;
    Eigen::MatrixXd Lanczos_QR;
    Eigen::MatrixXd Householder;
    Eigen::MatrixXd Householder_QR;
    Eigen::MatrixXd Random;
    Eigen::MatrixXd EV;

    Eigen::VectorXd time_lanczos(50);
    Eigen::VectorXd time_householder(50);
    Eigen::VectorXd time_eigensolver(50);

    std::clock_t begin;
    std::clock_t end;

    std::ofstream file ("build/task1c.txt");

    cout << "# N Lanczos Householder EigenSolver" << endl;
    file << "# N Lanczos Householder EigenSolver" << endl;
    for (int N = 3; N < 20; N++) {
        for (int i = 0; i < 50; i++) {
            // cout << N << " " << i+1 << endl;
            Random = Eigen::DenseBase<Eigen::MatrixXd>::Random(N, N);
            Eigen::VectorXd q = Eigen::VectorXd::Zero(N);
            q(0) = 1;

            begin = std::clock();
            Lanczos = lanczos(Random, q);
            Lanczos_QR = qr_iteration(Lanczos, Lanczos);
            end = std::clock();
            time_lanczos(i) = double(end - begin) / CLOCKS_PER_SEC;

            begin = std::clock();
            Householder = householder(Random);
            Householder_QR = qr_iteration(Householder, Householder);
            end = std::clock();
            time_householder(i) = double(end - begin) / CLOCKS_PER_SEC;

            begin = std::clock();
            Eigen::EigenSolver<Eigen::MatrixXd> ES(Random);
            EV = ES.eigenvalues().real();
            end = std::clock();
            time_eigensolver(i) = double(end - begin) / CLOCKS_PER_SEC;

        }
        cout << N << " "
             << time_lanczos.mean() << " "
             << time_householder.mean() << " "
             << time_eigensolver.mean() << endl;
        file << N << " "
             << time_lanczos.mean() << " "
             << time_householder.mean() << " "
             << time_eigensolver.mean() << endl;
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
