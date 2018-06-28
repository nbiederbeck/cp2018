// vim: commentstring=//%s expandtab shiftwidth=4
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include "physics.hpp"

using std::cout;
using std::endl;


Eigen::Vector4d initialize(const char* choice)
{
    Eigen::Vector4d init;

    init(0) = 0.0;
    init(1) = 0.0;
    init(2) = 0.0;
    if (choice == "periodic") {
        init(0) = 0.1;
        init(1) = std::sqrt(2.0) * init(0);
        init(3) = 0.0;
    } else if (choice == "quasi") {
        init(3) = 4.472;
    } else {
        init(3) = 11.832;
    }

    return init;
}

// // Haben Anfangszustaende richtige kinetische Energie?
// bool test_energy_init_states(Eigen::Vector4d state, const char* choice)
// {
//     double E = Ekin(state);
//     if (choice == "periodic") {
//         return false;
//     } else if (choice == "quasi") {
//         if (E == 10.0) {
//             return true;
//         } else {
//             return false;
//         }
//     } else {
//         if (E == 70.0) {
//             return true;
//         } else {
//             return false;
//         }
//     }
//     return true;
// }

void a(int N, double h)
{
    cout << "src/02.cpp:  (a) 3 Doppelpendel schwingen lassen." << endl;

    Eigen::Vector4d periodic = initialize("periodic");
    std::ofstream poincare_data_periodic;
    poincare_data_periodic.open("build/poincare_data_periodic.txt");

    Eigen::Vector4d quasi = initialize("quasi");
    std::ofstream poincare_data_quasi;
    poincare_data_quasi.open("build/poincare_data_quasi.txt");

    Eigen::Vector4d chaos = initialize("chaos");
    std::ofstream poincare_data_chaos;
    poincare_data_chaos.open("build/poincare_data_chaos.txt");


    for (int i = 0; i < N; ++i) {
        periodic = rungekutta(periodic, h);
        poincare_data_periodic
            << periodic(0) << " "
            << periodic(1) << " "
            << periodic(2) << " "
            << periodic(3) << " "
            << Epot(periodic) << " "
            << Ekin(periodic) << " "
            << endl;

        quasi = rungekutta(quasi, h);
        poincare_data_quasi
            << quasi(0) << " "
            << quasi(1) << " "
            << quasi(2) << " "
            << quasi(3) << " "
            << Epot(quasi) << " "
            << Ekin(quasi) << " "
            << endl;

        chaos = rungekutta(chaos, h);
        poincare_data_chaos
            << chaos(0) << " "
            << chaos(1) << " "
            << chaos(2) << " "
            << chaos(3) << " "
            << Epot(chaos) << " "
            << Ekin(chaos) << " "
            << endl;
    }
    cout << "src/02.cpp:  Done" << endl;
}


Eigen::Vector4d disturb(Eigen::Vector4d state)
{
    state(0) += 0.01;
    state(1) += 0.01;
    state(2) += 0.01;
    state(2) += 0.01;
    return state;
}


void b(int N, double h)
{
    cout << "src/02.cpp:  (b) 3 gestoerte Doppelpendel schwingen lassen." << endl;

    Eigen::Vector4d periodic = initialize("periodic");
    std::ofstream poincare_data_periodic;
    poincare_data_periodic.open("build/poincare_data_periodic_disturbed.txt");
    periodic = disturb(periodic);

    Eigen::Vector4d quasi = initialize("quasi");
    std::ofstream poincare_data_quasi;
    poincare_data_quasi.open("build/poincare_data_quasi_disturbed.txt");
    quasi = disturb(quasi);

    Eigen::Vector4d chaos = initialize("chaos");
    std::ofstream poincare_data_chaos;
    poincare_data_chaos.open("build/poincare_data_chaos_disturbed.txt");
    chaos = disturb(chaos);


    for (int i = 0; i < N; ++i) {
        periodic = rungekutta(periodic, h);
        poincare_data_periodic
            << periodic(0) << " "
            << periodic(1) << " "
            << periodic(2) << " "
            << periodic(3) << " "
            << Epot(periodic) << " "
            << Ekin(periodic) << " "
            << endl;

        quasi = rungekutta(quasi, h);
        poincare_data_quasi
            << quasi(0) << " "
            << quasi(1) << " "
            << quasi(2) << " "
            << quasi(3) << " "
            << Epot(quasi) << " "
            << Ekin(quasi) << " "
            << endl;

        chaos = rungekutta(chaos, h);
        poincare_data_chaos
            << chaos(0) << " "
            << chaos(1) << " "
            << chaos(2) << " "
            << chaos(3) << " "
            << Epot(chaos) << " "
            << Ekin(chaos) << " "
            << endl;
    }

    cout << "src/02.cpp:  Done" << endl;
}


int main()
{
    int N = 100000;
    double h = 0.0001;

    a(N, h);
    b(N, h);

    return 0;
}
