// vim: commentstring=//%s expandtab shiftwidth=4
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>
#include <ctime>
<<<<<<< HEAD
=======
#include "solutions.h"
>>>>>>> noah


using std::cout;
using std::endl;
<<<<<<< HEAD
using std::pow;


=======


Eigen::VectorXd force(Eigen::VectorXd r, double g)
{
    return - g * r / std::pow(r.norm(), 3);
}

// include here to overwrite "force()"
#include "euler.h"
#include "rungekutta.h"
#include "rungekutta_moon.h"


struct solutions energy(struct solutions sol, double m, double g, double alpha)
{
    Eigen::VectorXd energy(sol.r_i.cols());
    Eigen::VectorXd momentum(sol.r_i.cols());

    for (int i = 0; i < sol.r_i.cols(); i++) {
        energy(i) =
            + m / 2. * sol.v_i.col(i).squaredNorm()  // kinetische Energie
            - m * g / std::pow(sol.r_i.col(i).norm(), alpha);  // potentielle Energie
        momentum(i) =  // betrag des dehimpulses
            m * static_cast<Eigen::Vector3d>(sol.r_i.col(i))
                .cross(static_cast<Eigen::Vector3d>(sol.v_i.col(i)))
                .squaredNorm();
    }

    sol.energy = energy;
    sol.momentum = momentum;

    return sol;
}


void save(struct solutions sol, double T, const std::string &filename)
{
    std::string path = "build/"+ filename + "/";
    std::system(("mkdir -p "+path).c_str());
    std::ofstream file;

    file.open(path+"T.txt");
    file << T << std::endl;
    file.close();

    file.open(path+"r_i.txt");
    file << sol.r_i << std::endl;
    file.close();

    file.open(path+"v_i.txt");
    file << sol.v_i << std::endl;
    file.close();

    file.open(path+"r_i_moon.txt");
    file << sol.r_i_moon << std::endl;
    file.close();

    file.open(path+"v_i_moon.txt");
    file << sol.v_i_moon << std::endl;
    file.close();

    file.open(path+"energy.txt");
    file << sol.energy << std::endl;
    file.close();

    file.open(path+"momentum.txt");
    file << sol.momentum << std::endl;
    file.close();
}

void c(double h) {
    // setze Start/Rand-bedingugen
    double T = 1. * 24.;  // day = 24 hours
    const int dim = 3;
    double mass = 1.;
    double g = 1.;  // gravitational constant
    double alpha = 0.9;  // exponent of potential

    // initialize start vectors
    Eigen::VectorXd r_0(dim);
    Eigen::VectorXd v_0(dim);
    r_0 << 1.0, 0.0, 0.0;
    v_0 << 0.37, 1.0, 0.0;

    cout << "./bin/02.cpp: (c) 0/2" << endl;
    struct solutions _2c09 = rungekutta(h, T, r_0, v_0, mass, g);
    _2c09 = energy(_2c09, mass, g, alpha);
    save(_2c09, T, "_2c09");
    cout << "./bin/02.cpp: (c) 1/2" << endl;

    alpha = 1.1;
    struct solutions _2c11 = rungekutta(h, T, r_0, v_0, mass, g);
    _2c11 = energy(_2c11, mass, g, alpha);
    save(_2c11, T, "_2c11");
    cout << "./bin/02.cpp: (c) 2/2" << endl;
}

void d(double h) {
    // setze Start/Rand-bedingugen
    double T = 1. * 24.;  // day = 24 hours
    const int dim = 3;
    double mass_planet = 1.;
    double mass_moon = 0.01 * mass_planet;
    double g = 1.;  // gravitational constant
    double alpha = 1.0;  // exponent of potential

    // initialize start vectors
    Eigen::VectorXd r_0_planet(dim);
    Eigen::VectorXd v_0_planet(dim);
    r_0_planet << 1.0, 0.0, 0.0;
    v_0_planet << 0.0, std::sqrt(3./2.), 0.0;
    // v_0_planet << 0.0, 0.8, 0.0;

    Eigen::VectorXd r_0_moon(dim);
    Eigen::VectorXd v_0_moon(dim);
    r_0_moon << 1.1, 0.0, 0.0;
    v_0_moon << 0.0, 4.7, 0.0;

    cout << "./bin/02.cpp: (d) 0/1" << endl;
    struct solutions kepler_rungekutta_moon = rungekutta_moon(
        h, T, r_0_planet, v_0_planet, r_0_moon, v_0_moon, mass_planet, mass_moon, g
    );
    // kepler_rungekutta_moon = energy(kepler_rungekutta_moon, mass_planet, g, alpha);

    save(kepler_rungekutta_moon, T, "kepler_moon");
    cout << "./bin/02.cpp: (d) 1/1" << endl;
}

int main()
{
    // setze Start/Rand-bedingugen
    double T = 1. * 24.;  // day = 24 hours
    double h = 1. / 5500.; //* if slow: */ h*=10.;
    const int dim = 3;
    double mass = 1.;
    double g = 1.;  // gravitational constant
    double alpha = 1.0;  // exponent of potential

    // initialize start vectors
    Eigen::VectorXd r_0(dim);
    Eigen::VectorXd v_0(dim);
    r_0 << 1.0, 0.0, 0.0;
    v_0 << 0.37, 1.0, 0.0;

    // calculate and save kepler motion

    cout << "./bin/02.cpp: (a,b) 0/2" << endl;
    struct solutions kepler_euler = euler(h, T, r_0, v_0, mass, g);
    kepler_euler = energy(kepler_euler, mass, g, alpha);
    save(kepler_euler, T, "kepler_euler");
    cout << "./bin/02.cpp: (a,b) 1/2" << endl;

    struct solutions kepler_rungekutta = rungekutta(h, T, r_0, v_0, mass, g);
    kepler_rungekutta = energy(kepler_rungekutta, mass, g, alpha);
    save(kepler_rungekutta, T, "kepler_rungekutta");
    cout << "./bin/02.cpp: (a,b) 2/2" << endl;

    c(h);
    d(h);


    return 0;
}
>>>>>>> noah
