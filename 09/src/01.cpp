// vim: commentstring=//%s expandtab shiftwidth=4
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
// #include "physics.hpp"

using std::cout;
using std::endl;

Eigen::MatrixXd initialize(int N=16, double L=1.0)
{
    Eigen::MatrixXd init(4, N);
    int i = 0;

    for (double n = 0.0; n <= 3.0; ++n) {
        for (double m = 0.0; m <= 3.0; ++m) {
            init.col(i) << L / 8.0 * (1.0 + 2.0 * n), L / 8.0 * (1.0 + 2.0 * m), 0.0, 0.0;
            ++i;
        }
    }

    return init;
}

void a()
{
    int N = 16;
    Eigen::MatrixXd init = initialize();
    cout << init << endl;
}

int main() {
    a();
    return 0;
}
