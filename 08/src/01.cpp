// vim: commentstring=//%s expandtab shiftwidth=4
#include "Eigen/Dense"
#include <iostream>
#include <fstream>

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

Eigen::Vector4d euler(Eigen::Vector4d state, double h)
{
    double g = 1.0;
    Eigen::Vector4d next;

    next(0) = state(0) + h * state(2);
    next(1) = state(1) + h * state(3);
    next(2) = state(2) + h * 2.0 * g * (state(1) - 2.0 * state(0));
    next(3) = state(3) + h * 2.0 * g * (state(0) - 1.0 * state(1));

    return next;
}

// double phi_1(vector<double> y){
//   double phi1;

//   double Vorfaktor = mu * cos(y[1] - y[0]) * cos(y[1] - y[0]);
//   Vorfaktor = 1 - Vorfaktor;
//   Vorfaktor = 1 / Vorfaktor;

//   double f1 = mu * g1 * sin(y[1]) * cos(y[1] - y[0]);
//   double f2 = mu * y[2] * y[2] * sin(y[1] - y[0]) * cos(y[1] - y[0]);
//   double f3 = -g1 * sin(y[0]);
//   double f4 = (mu / lambda) * y[3] * y[3] * sin(y[1] - y[0]);

//   phi1 = Vorfaktor * (f1 + f2 + f3 + f4);
//   return phi1;
// }

// double phi_2(vector<double> y){
//   double phi2;

//   double Vorfaktor = mu * cos(y[1] - y[0]) * cos(y[1] - y[0]);
//   Vorfaktor = 1 - Vorfaktor;
//   Vorfaktor = 1 / Vorfaktor;

//   double f1 = g2 * sin(y[0]) * cos(y[1] - y[0]);
//   double f2 = -mu * y[3] * y[3] * sin(y[1] - y[0]) * cos(y[1] - y[0]);
//   double f3 = -g2 * sin(y[1]);
//   double f4 = -lambda * y[2] * y[2] * sin(y[1] - y[0]);

//   phi2 = Vorfaktor * (f1 + f2 + f3 + f4);
//   return phi2;
// }

void b()
{
    cout << "b) Testen, ob System in der Naeherung schwingt." << endl;

    Eigen::Vector4d init = initialize(false);
    Eigen::Vector4d state = init;

    std::ofstream pendulum_data;
    pendulum_data.open("build/pendulum_data_b.txt");

    for (int i; i < 100000; ++i) {
        state = euler(state, 0.001);

        pendulum_data << state(0) << " " << state(1) << endl;
    }

    cout << "Done" << endl << endl;
}

int main()
{
    b();
    return 0;
}
