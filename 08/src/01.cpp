// vim: commentstring=//%s expandtab shiftwidth=4
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include "physics.hpp"

using std::cout;
using std::endl;

Eigen::Vector4d initialize(bool sign)
{
    Eigen::Vector4d init;

    init(0) = 0.1;
    init(1) = std::sqrt(2.0) * init(0);
    if (sign)
        init(1) *= -1.0;
    init(2) = 0.0;
    init(3) = 0.0;

    return init;
}


void b()
{
    cout << "src/01.cpp:  (b) Testen, ob System in der Naeherung schwingt (Euler Verfahren)." << endl;

    Eigen::Vector4d init = initialize(false);
    Eigen::Vector4d state = init;

    std::ofstream pendulum_data;
    pendulum_data.open("build/pendulum_data_b.txt");

    for (int i; i < 100000; ++i) {
        state = euler(state, 0.001);

        pendulum_data
            << state(0) << " "
            << state(1) << " "
            << state(2) << " "
            << state(3) << " "
            << endl;
    }

    cout << "src/01.cpp:  Done" << endl << endl;
}

void c(int N, double h)
{
    cout << "src/01.cpp:  (c) Schwingungen mit Runge-Kutta 4. Ordnung." << endl;

    // Vorzeichen +
    Eigen::Vector4d state_plus = initialize(false);
    std::ofstream pendulum_data_plus;
    pendulum_data_plus.open("build/pendulum_data_c_plus.txt");

    // Vorzeichen -
    Eigen::Vector4d state_minus = initialize(true);
    std::ofstream pendulum_data_minus;
    pendulum_data_minus.open("build/pendulum_data_c_minus.txt");

    for (int i; i < N; ++i) {
        state_plus = rungekutta(state_plus, h);
        pendulum_data_plus
            << state_plus(0) << " "     // theta 1
            << state_plus(1) << " "     // theta 2
            << state_plus(2) << " "     // theta 1 punkt
            << state_plus(3) << " "     // theta 2 punkt
            << Epot(state_plus) << " "  // potentielle Energie
            << Ekin(state_plus) << " "  // kinetische Energie
            << endl;

        state_minus = rungekutta(state_minus, h);
        pendulum_data_minus
            << state_minus(0) << " "     // theta 1
            << state_minus(1) << " "     // theta 2
            << state_minus(2) << " "     // theta 1 punkt
            << state_minus(3) << " "     // theta 2 punkt
            << Epot(state_minus) << " "  // potentielle Energie
            << Ekin(state_minus) << " "  // kinetische Energie
            << endl;
    }

    cout << "src/01.cpp:  Done" << endl << endl;
}

int main()
{
    int N = 100000;
    double h = 0.0001;
    b();
    c(N, h);
    return 0;
}
