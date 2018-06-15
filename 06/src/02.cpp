// vim: commentstring=//%s expandtab shiftwidth=4
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>
#include <ctime>


using std::cout;
using std::endl;
using std::pow;


double kronecker(int i, int j) {
    if (i == j)
        return 1.0;
    else
        return 0.0;
}


// calculate hamiltonian from equations (3,4)
Eigen::MatrixXd hamiltonian(double lambda, double L, double delta_xi) {
    double dim = 1 + 2 * (L / delta_xi);

    double first = - (L / delta_xi);
    double next = first;

    Eigen::MatrixXd H = Eigen::MatrixXd::Zero(dim, dim);

    for (int n = 0; n < static_cast<int>(dim); n++) {
        next = first + n * delta_xi;
        for (int m = 0; m < static_cast<int>(dim); m++) {
            H(n, m) =
                - (1.0 / pow(delta_xi, 2))
                * (kronecker(n, m-1) + kronecker(n, m+1) - 2 * kronecker(n, m))
                + (
                        pow(delta_xi, 2) * pow(n, 2)
                        + lambda * pow(delta_xi, 4) * pow(n, 4)
                  ) * kronecker(n, m);
        }
    }
    return H;
}

// calculate hamiltonian from equations (3,4)
// Eigen::MatrixXd epsilon4(int N, int M) {

//     Eigen::MatrixXd H = Eigen::MatrixXd::Zero(N, M);

//     for (int n = 0; n < N; n++) {
//         for (int m = 0; m < M; m++) {
//             H(n, m) =
//                 - (1.0 / pow(delta_xi, 2))
//                 * (kronecker(n, m-1) + kronecker(n, m+1) - 2 * kronecker(n, m))
//                 + (
//                         pow(delta_xi, 2) * pow(next, 2)
//                         + lambda * pow(delta_xi, 4) * pow(next, 4)
//                   ) * kronecker(n, m);
//         }
//     }
//     return H;
// }


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
    double delta_xi = 0.01;

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


int main()
{
    cout << "Task 2" << endl << "======" << endl << endl
         << "(b)" << endl << "---" << endl << endl;
    b();
    // cout << "(c)" << endl << "---" << endl << endl;
    // c();
    // cout << "(d)" << endl << "---" << endl << endl;
    // d();
    return 0;
}
