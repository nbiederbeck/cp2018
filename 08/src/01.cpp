// vim: commentstring=//%s expandtab shiftwidth=4
#include "Eigen/Dense"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

struct pendulum {
    Eigen::MatrixXd theta;
    Eigen::MatrixXd theta_;
};

Eigen::VectorXd force(Eigen::VectorXd vec, double k)
{
    return vec;
}
#include "rungekutta.h"

pendulum initialize(bool sign)
{
    // Startbedingungen
    struct pendulum init;
    Eigen::VectorXd theta0(2);
    Eigen::VectorXd theta_0(2);

    theta_0 << 0, 0;
    init.theta_ = theta_0;

    if (!sign) {
        theta0 << 0.1, std::sqrt(2.0) * 0.1;
    } else {
        theta0 << 0.1, - std::sqrt(2.0) * 0.1;
    }
    init.theta = theta0;

    return init;
}

pendulum euler(pendulum state, double h)
{
    double g = 1.0;
    pendulum next;
    // Temporary stuff
    Eigen::VectorXd temp(2);
    temp << 0, 0;
    next.theta = temp;
    next.theta_ = temp;
    // Physics
    next.theta(0) = state.theta(0) + h * state.theta_(0);
    next.theta(1) = state.theta(1) + h * state.theta_(1);
    next.theta_(0) = state.theta_(0) + h * 2.0 * g * (state.theta(1) - 2.0 * state.theta(0));
    next.theta_(1) = state.theta_(1) + h * 2.0 * g * (state.theta(0) - 1.0 * state.theta(1));
    return next;
}

void b()
{
    cout << "Testen, ob System in der Naeherung schwingt." << endl;
    pendulum init = initialize(false);

    pendulum state = init;

    std::ofstream pendulum_data;
    pendulum_data.open("build/pendulum_data_b.txt");
    for (int i; i < 100000; ++i) {
        state = euler(state, 0.001);

        pendulum_data << state.theta(0) << " " << state.theta(1) << endl;
    }
    cout << "Done" << endl << endl;
}

int main()
{
    b();
    return 0;
}
