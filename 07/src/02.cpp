// vim: commentstring=//%s expandtab shiftwidth=4
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>
#include <ctime>


using std::cout;
using std::endl;
using std::pow;


Eigen::VectorXd force(Eigen::VectorXd r, double g)
{
    return -g * r / pow(r.norm(), 3);
}
#include "euler.h"  // include here to overwrite "force()"


struct solutions energy(struct solutions sol, double m, double g, double alpha)
{
    Eigen::VectorXd energy(sol.r_i.cols());

    for (int i = 0; i < sol.r_i.cols(); i++) {
        energy(i) =
            - m / 2. * sol.v_i.col(i).squaredNorm()  // kinetische Energie
            + m * g / pow(sol.r_i.col(i).norm(), alpha);  // potentielle Energie
    }

    sol.energy = energy;

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

    file.open(path+"energy.txt");
    file << sol.energy << std::endl;
    file.close();
}


int main()
{
    // setze Start/Rand-bedingugen
    double T = 24.;  // day = 24 hours
    double h = 1. / 5000.; /* if slow: */ h*=10;
    const int dim = 3;
    double mass = 1.;
    double g = 1.;  // gravitational constant
    double alpha = 1.0;  // exponent of potential

    // initialize start vectors
    Eigen::VectorXd r_0(dim);
    Eigen::VectorXd v_0(dim);
    r_0 << 1.0, 0.0, 0.0;
    v_0 << 0.0, 0.9, 0.0;

    // calculate and save kepler motion
    struct solutions kepler = euler(h, T, r_0, v_0, mass, g);
    kepler = energy(kepler, mass, g, alpha);
    save(kepler, T, "kepler");

    return 0;
}
