// vim: commentstring=//%s expandtab shiftwidth=4
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>
#include <ctime>


using std::cout;
using std::endl;


double kronecker(int i, int j) {
    if (i == j)
        return 1.0;
    else
        return 0.0;
}


// calculate hamiltonian from equations (3,4)
Eigen::MatrixXd hamiltonian(double lambda, double L, double delta_xi) {
    int dim = 1 + 2 * (L / delta_xi);

    double n_ = - (L / delta_xi);

    Eigen::MatrixXd H = Eigen::MatrixXd::Zero(dim, dim);

    for (int n = 0; n < dim; n++) {
        for (int m = 0; m < dim; m++) {
            H(n, m) =
                - (1.0 / std::pow(delta_xi, 2))
                * (kronecker(n, m-1) + kronecker(n, m+1) - 2 * kronecker(n, m))
                + (
                        std::pow(delta_xi, 2) * std::pow(n_, 2)
                        + lambda * std::pow(delta_xi, 4) * std::pow(n_, 4)
                  ) * kronecker(n, m);
        }
        n_++;
    }
    return H;
}


// calculate hamiltonian from equation (9)
Eigen::MatrixXd hamiltonian_new(double lambda, int dim, double delta_xi) {
    Eigen::MatrixXd H = Eigen::MatrixXd::Zero(dim, dim);

    for (int n = 0; n < dim; n++) {
        for (int m = 0; m < dim; m++) {
            H(n, m) =
                - (1.0 / std::pow(delta_xi, 2))
                * (kronecker(n, m-1) + kronecker(n, m+1) - 2 * kronecker(n, m))
                + 0.25 * (
                        std::sqrt(m * (m-1) * (m-2) * (m-3)) * kronecker(n, m-4)
                        + std::sqrt((m+1) * (m+2) * (m+3) * (m+4)) * kronecker(n, m+4)
                        + std::sqrt(m * (m-1)) * (4 * m - 2) * kronecker(n, m-2)
                        + std::sqrt((m+1) * (m+2)) * (4 * m + 6) * kronecker(n, m+2)
                        + (6 * std::pow(m, 2) + 6 * m + 3) * kronecker(n, m)
                  );
        }
    }
    return H;
}


Eigen::VectorXd lowest_ev(Eigen::VectorXd ev, int N = 10) {
    Eigen::VectorXd low_ev(N);
    std::sort(ev.data(), ev.data() + ev.size());
    for (int i = 0; i < N; i++) {
        low_ev(i) = ev(i);
    }
    return low_ev;
}


void b() {
    std::ofstream file ("build/task2b.txt");

    double lambda = 0.0;
    double L = 10.0;
    double delta_xi = 0.1;

    Eigen::MatrixXd H_0 = hamiltonian(lambda, L, delta_xi);
    Eigen::EigenSolver<Eigen::MatrixXd> ES_0(H_0);
    Eigen::VectorXd EV_0 = ES_0.eigenvalues().real();

    cout << "# Eigenwerte fuer lambda=" << lambda << endl
         << lowest_ev(EV_0) << endl << endl;
    file << "# Eigenwerte fuer lambda=" << lambda << endl
         << lowest_ev(EV_0) << endl;

    lambda = 0.2;

    Eigen::MatrixXd H_02 = hamiltonian(lambda, L, delta_xi);
    Eigen::EigenSolver<Eigen::MatrixXd> ES_02(H_02);
    Eigen::VectorXd EV_02 = ES_02.eigenvalues().real();

    cout << "# Eigenwerte fuer lambda=" << lambda << endl
         << lowest_ev(EV_02) << endl << endl;
    file << "# Eigenwerte fuer lambda=" << lambda << endl
         << lowest_ev(EV_02) << endl;
}


void c() {
    std::ofstream file ("build/task2c.txt");

    double lambda = 0.2;
    double L = 10;
    int N = 50;
    double delta_xi = 2 * L / N;

    Eigen::MatrixXd H = hamiltonian_new(lambda, N, delta_xi);
    Eigen::EigenSolver<Eigen::MatrixXd> ES(H);
    Eigen::VectorXd EV = ES.eigenvalues().real();

    cout << "# Eigenwerte fuer lambda=" << lambda << endl
         << lowest_ev(EV) << endl << endl;
    file << "# Eigenwerte fuer lambda=" << lambda << endl
         << lowest_ev(EV) << endl;
}


void d() {
    std::ofstream file ("build/task2d.txt");
    std::ofstream file_new ("build/task2d_new.txt");

    double lambda = 0.2;
    double L = 10;
    double delta_xi = 0;

    Eigen::MatrixXd H;
    Eigen::VectorXd EV;

    file << "# Eigenwerte fuer lambda=" << lambda << ", (b)" << endl;
    file_new << "# Eigenwerte fuer lambda=" << lambda << ", (c)" << endl;

    for (int N = 10; N < 100; N = N+2) {
        delta_xi = 2 * L / N;
        H = hamiltonian(lambda, L, delta_xi);
        Eigen::EigenSolver<Eigen::MatrixXd> ES(H);
        cout << N << " " << lowest_ev(ES.eigenvalues().real()) << endl << endl;
        file << N << endl << lowest_ev(ES.eigenvalues().real()) << endl;

        H = hamiltonian_new(lambda, N, delta_xi);
        Eigen::EigenSolver<Eigen::MatrixXd> ES_new(H);
        cout << N << " " << lowest_ev(ES_new.eigenvalues().real()) << endl << endl;
        file_new << N << endl << lowest_ev(ES_new.eigenvalues().real()) << endl;
    }

}


int main()
{
    cout << "Task 2" << endl << "======" << endl << endl
         << "(b)" << endl << "---" << endl << endl;
    b();
    cout << "(c)" << endl << "---" << endl << endl;
    c();
    cout << "(d)" << endl << "---" << endl << endl;
    d();
    return 0;
}
