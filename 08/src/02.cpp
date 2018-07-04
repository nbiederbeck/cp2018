// vim: commentstring=//%s expandtab shiftwidth=4
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <random>
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

    std::ofstream poincare_data_periodic_cut;
    poincare_data_periodic_cut.open("build/poincare_data_periodic_cut.txt");


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

        if (std::fabs(periodic(1)) <= std::pow(1,-5) && periodic(3) + 1.0 * periodic(2) * std::cos(periodic(0)) > 0) {
            poincare_data_periodic_cut
                << periodic(0) << " "
                << periodic(1) << " "
                << periodic(2) << " "
                << periodic(3) << " "
                << Epot(periodic) << " "
                << Ekin(periodic) << " "
                << endl;
        }
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

    template <typename T>
T interpol_linear(T const& x_1, T const& x_2, T const& y_1, T const& y_2)
{
    T m = (y_2 - y_1)/(x_2 - x_1);
    return y_2 - m * x_2;
}

Eigen::Vector4d init_start_conditions(double E)
{
    Eigen::Vector4d init;

    // 1/2(theta_1_p^2 + theta_1_p^2) = E => Theta_1_p < sqrt(2E)
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> theta_p(-std::sqrt(2*E), std::sqrt(2*E));

    double theta_1_p = theta_p(rd);

    init << 0, 0, theta_1_p, std::sqrt(2*E - std::pow(theta_1_p,2));
    return init;
}

void gen_poincare_cuts(double E, int anzahl_start, const char *filename, int N, double h)
{
    Eigen::Vector4d periodic;
    Eigen::Vector4d p_next;

    std::ofstream poincare_low_energy;
    poincare_low_energy.open(filename);

    // fuer mehrere Startbedingungen
    for(int n = 0; n<anzahl_start; n++){
        periodic = init_start_conditions(E);

        // Runge Kutter fuer die Anzahl an Stuetzstellen
        for (int i = 0; i < N; ++i) {
            p_next = rungekutta(periodic, h);
            if (periodic(1) * p_next(1) < 0 && periodic(3) + 1.0 * periodic(2) 
                    * std::cos(periodic(0)) > 0) 
            {
                poincare_low_energy << interpol_linear(p_next(1), periodic(1), p_next(0), periodic(0)) << " "; 
                poincare_low_energy << interpol_linear(p_next(1), periodic(1), p_next(2), periodic(2)) << std::endl; 
            }
            periodic = p_next;
        }
    }

}

void c(int N, double h)
{
    // Eigen::Vector4d init;

    // init << 0.1, std::sqrt(2.0) * init(0), 0.0, 0.0;

    // Eigen::Vector4d periodic = initialize("periodic");
    // Eigen::Vector4d p_next;

    // std::ofstream poincare_low_energy;
    // poincare_low_energy.open("build/poincare_low_energy.txt");

    // cout << "start params: " << init_start_conditions(10) << endl;


    // for (int i = 0; i < N; ++i) {
    //     p_next = rungekutta(periodic, h);
    //     if (periodic(1) * p_next(1) < 0 && periodic(3) + 1.0 * periodic(2) 
    //             * std::cos(periodic(0)) > 0) 
    //     {
    //         poincare_low_energy << interpol_linear(p_next(1), periodic(1), p_next(0), periodic(0)) << " "; 
    //         poincare_low_energy << interpol_linear(p_next(1), periodic(1), p_next(2), periodic(2)) << std::endl; 
    //     }
    //     periodic = p_next;
    // }

    gen_poincare_cuts(1, 10, "build/poincare_c_1.txt", N, h);
    gen_poincare_cuts(10, 50, "build/poincare_c_10.txt", N, h);
    gen_poincare_cuts(70, 300, "build/poincare_c_70.txt", N, h);
}

int main()
{
    int N = 100000;
    double h = 0.001;

    a(N, h);
    b(N, h);
    c((int)1e6, 0.001);

    return 0;
}
