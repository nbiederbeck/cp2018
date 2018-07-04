// vim: commentstring=//%s expandtab shiftwidth=4
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>
<<<<<<< HEAD
<<<<<<< HEAD
#include <ctime>
#include <vector>

=======
#include <vector>
#include <string>
>>>>>>> origin/maxi

using std::cout;
using std::endl;
using std::vector;

<<<<<<< HEAD
vector<double> diskretisierung(double t_0, double T, int h){
=======
vector<double> diskretisierung(double t_0, double T, int h)
{
>>>>>>> origin/maxi
    vector<double> t = {t_0};
    for(int i=1; i<=h; i++){
        t.push_back(t_0 + T/h * i);
    }
    return t;
}

<<<<<<< HEAD
double func(double x){
    return std::pow(x,2);
}

double stepsize(vector<double> t, int i){
    return t[i] - t[i-1];
}

struct solutions {
    vector<double> r_i;
    vector<double> v_i;
};

struct solutions euler(vector<double> t_i, double r_0, double v_0){
    vector<double> r_i = {r_0};
    vector<double> v_i = {v_0};

    double omega = 1.;

    for(int i=1; i<t_i.size(); i++){
        v_i.push_back(
                v_i[i-1] - stepsize(t_i,i) * pow(omega,2) * r_i[i-1]
                );
        r_i.push_back(
                r_i[i-1] + stepsize(t_i,i) * pow(omega,2) * v_i[i-1]
                );
    }
    solutions s_euler ;
    s_euler.r_i = r_i; s_euler.v_i = v_i;
    return s_euler;
}

struct solutions runge(vector<double> t_i, double r_0, double v_0){
    vector<double> r_i = {r_0};
    vector<double> v_i = {v_0};

    double omega = 1.;

    for(int i=1; i<t_i.size(); i++){
        v_i.push_back(
                v_i[i-1] - stepsize(t_i,i) * pow(omega,2) * r_i[i-1]
                );
        r_i.push_back(
                r_i[i-1] + stepsize(t_i,i) * pow(omega,2) * v_i[i-1]
                );
=======
// #include <vector>
#include <string>
#include "solutions.h"
=======
double stepsize(vector<double> t, int i)
{
    return t[i+1] - t[i];
}

struct solutions {
    Eigen::MatrixXd r_i;
    Eigen::MatrixXd v_i;
    Eigen::VectorXd energy;
};
>>>>>>> origin/maxi

using std::cout;
using std::endl;
// using std::vector;

// vector<double> diskretisierung(double t_0, double T, int h)
// {
//     vector<double> t = {t_0};
//     for(int i=1; i<=h; i++){
//         t.push_back(t_0 + T/h * i);
//     }
//     return t;
// }

// double stepsize(vector<double> t, int i)
// {
//     return t[i+1] - t[i];
// }

// struct solutions {
//     Eigen::MatrixXd r_i;
//     Eigen::MatrixXd v_i;
//     Eigen::VectorXd energy;
// };

// Eigen::VectorXd func(double t, Eigen::VectorXd x_i)
// {
//     // die funktion haengt explizit nicht von t ab
//     double omega = 1;
//     return pow(omega,2) * x_i;
// }

Eigen::VectorXd force(Eigen::VectorXd r, double k)
{
    return -k * r;
}


struct solutions euler(
        double h,  // schrittlaenge
        int T,  // obere integrationsgrenze
        Eigen::VectorXd r_0,
        Eigen::VectorXd v_0,
        double mass,
        double k) // lineare rueckstellkraft
{
    Eigen::MatrixXd r_i = r_0;
    Eigen::MatrixXd v_i = v_0;

    Eigen::VectorXd r_n(r_0.rows());
    Eigen::VectorXd v_n(r_0.rows());

    for(int i = 0; i < T / h; i++){
        Eigen::MatrixXd joined_r_i(r_i.rows(), r_i.cols()+1);
        Eigen::MatrixXd joined_v_i(r_i.rows(), r_i.cols()+1);

        // physics
        v_n << v_i.col(i) + h * force(r_i.col(i), k) / mass;
        r_n << r_i.col(i) + h * v_i.col(i);

        // fill old var with new values
        joined_r_i << r_i, r_n;
        r_i = joined_r_i;
        joined_v_i << v_i, v_n;
        v_i = joined_v_i;
    }
    struct solutions eul;
    eul.r_i = r_i;
    eul.v_i = v_i;
    return eul;
}

struct solutions rungekutta_2(double h, int T, Eigen::VectorXd r_0, Eigen::VectorXd v_0, double k, double mass)
{
    Eigen::MatrixXd r_i = r_0;
    Eigen::MatrixXd v_i = v_0;

    Eigen::VectorXd r_n(r_0.rows());
    Eigen::VectorXd v_n(r_0.rows());

    Eigen::VectorXd k1(r_0.rows() + v_0.rows());
    Eigen::VectorXd k2(r_0.rows() + v_0.rows());

    for (int i = 0; i < T / h; i++) {
        Eigen::MatrixXd joined_r_i(r_i.rows(), r_i.cols()+1);
        Eigen::MatrixXd joined_v_i(r_i.rows(), r_i.cols()+1);

        // physics
        r_n << r_i.col(i) + h * v_i.col(i) - h * h / 2.0 * r_i.col(i);
        v_n << v_i.col(i) - h * r_i.col(i) - h * h / 2.0 * v_i.col(i);
        // // v, y_1
        // k1 = h * force(r_i.col(i), k) / mass;
        // k2 = h * force(r_i.col(i) + 0.5 * k1, k) / mass;
        // v_n << v_i.col(i) + k2;
        // // r, y_0
        // k1 = h * v_i.col(i);
        // k2 = h * (v_i.col(i) + 0.5 * k1);
        // r_n << r_i.col(i) + k2;

        // fill old var with new values
        joined_r_i << r_i, r_n;
        r_i = joined_r_i;
        joined_v_i << v_i, v_n;
        v_i = joined_v_i;
    }
    struct solutions rk2;
    rk2.r_i = r_i;
    rk2.v_i = v_i;
    return rk2;
}

struct solutions rungekutta_4(double h, int T, Eigen::VectorXd r_0, Eigen::VectorXd v_0, double k, double mass)
{
    Eigen::MatrixXd r_i = r_0;
    Eigen::MatrixXd v_i = v_0;

    Eigen::VectorXd r_n(r_0.rows());
    Eigen::VectorXd v_n(r_0.rows());

    Eigen::VectorXd k1(r_0.rows());
    Eigen::VectorXd k2(r_0.rows());
    Eigen::VectorXd k3(r_0.rows());
    Eigen::VectorXd k4(r_0.rows());

    for(int i = 0; i < T / h; i++){
        // init help var
        Eigen::MatrixXd joined_r_i(r_i.rows(), r_i.cols()+1);
        Eigen::MatrixXd joined_v_i(r_i.rows(), r_i.cols()+1);

        // physics
        k1 = h * force(r_i.col(i), k) / mass;
        k2 = h * force(r_i.col(i) + 0.5 * k1, k) / mass;
        k3 = h * force(r_i.col(i) + 0.5 * k2, k) / mass;
        k4 = h * force(r_i.col(i) + 1.0 * k3, k) / mass;
        v_n << v_i.col(i) + 1./6. * (k1 + 2 * k2 + 2 * k3 + k4);

        k1 = h * v_i.col(i);
        k2 = h * (v_i.col(i) + 0.5 * k1);
        k3 = h * (v_i.col(i) + 0.5 * k2);
        k4 = h * (v_i.col(i) + 1.0 * k3);
        r_n << r_i.col(i) + 1./6. * (k1 + 2 * k2 + 2 * k3 + k4);

        // k_1 << func(t_i[i], v_i.col(i-1));
        // k_2 << func(t_i[i] + 1./2* stepsize(t_i,i), v_i.col(i-1) + stepsize(t_i,i)*1./2*k_1);
        // k_3 << func(t_i[i] + 1./2* stepsize(t_i,i), v_i.col(i-1) + stepsize(t_i,i)*1./2*k_2);
        // k_4 << func(t_i[i] + 2./2* stepsize(t_i,i), v_i.col(i-1) + stepsize(t_i,i)*2./2*k_3);
        // r_n << r_i.col(i-1) - stepsize(t_i,i) * (1./6 * k_1 + 1./3 * k_2 + 1./3 * k_3 + 1./6 * k_4);

        // k_1 << func(t_i[i], r_i.col(i-1));
        // k_2 << func(t_i[i] + 1./2* stepsize(t_i,i), r_i.col(i-1) +stepsize(t_i,i)*1./2*k_1);
        // k_3 << func(t_i[i] + 1./2* stepsize(t_i,i), r_i.col(i-1) +stepsize(t_i,i)*1./2*k_2);
        // k_4 << func(t_i[i] + 2./2* stepsize(t_i,i), r_i.col(i-1) +stepsize(t_i,i)*2./2*k_3);
        // v_n << v_i.col(i-1) + stepsize(t_i,i) * (1./6 * k_1 + 1./3 * k_2 + 1./3 * k_3 + 1./6 * k_4);

        // fill old var with new values
        joined_r_i << r_i, r_n;
        r_i = joined_r_i;
        joined_v_i << v_i, v_n;
        v_i = joined_v_i;
<<<<<<< HEAD
>>>>>>> noah
=======
>>>>>>> origin/maxi
    }
    solutions s_euler ;
    s_euler.r_i = r_i; s_euler.v_i = v_i;
    return s_euler;
}

<<<<<<< HEAD
<<<<<<< HEAD
int main(int argc, char *argv[])
{

    double t_0 = 0;
    double T = 10.;
    int h = 20;

    // euler solution
    vector<double> t_i = diskretisierung(t_0, T, h);
    struct solutions s_euler = euler(t_i, 0, 1);

    // save data
    std::ofstream file ("build/euler.txt");
    file << T << "; " << std::endl;
    for(unsigned i = 0; i< s_euler.r_i.size(); ++i) {
        file << s_euler.r_i[i] << "; " << s_euler.v_i[i] << std::endl;
    }
    
=======
=======
>>>>>>> origin/maxi
struct solutions energy(struct solutions sol, double m, double k) {
    Eigen::VectorXd energy(sol.r_i.cols());

    for (int i = 0; i < sol.r_i.cols(); i++) {
        energy(i) =
            m / 2. * sol.v_i.col(i).squaredNorm()  // kinetische Energie
            + k / 2. * sol.r_i.col(i).squaredNorm();  // potentielle Energie
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

    // setze Start/Randbedingugen
    double T = 4. * M_PI;
    double h = 0.01;
    const int dim = 3;
    double mass = 1.;
    double k = 1.;

    cout << "./bin/01.cpp: (a) 0/3" << endl;
    // initaliziere Startvektoren
    Eigen::VectorXd r_0(dim);
    Eigen::VectorXd v_0(dim);
    r_0 << 1, 0, 0;
    v_0 << 0, 0, 0;

    struct solutions s_euler = euler(h, T, r_0, v_0, mass, k);
    s_euler = energy(s_euler, mass, k);
    save(s_euler, T, "euler");
    cout << "./bin/01.cpp: (a) 1/3" << endl;

    struct solutions s_runge2 = rungekutta_2(h, T, r_0, v_0, mass, k);
    s_runge2 = energy(s_runge2, mass, k);
    save(s_runge2, T, "runge2");
    cout << "./bin/01.cpp: (a) 2/3" << endl;

    struct solutions s_runge4 = rungekutta_4(h, T, r_0, v_0, mass, k);
    s_runge4 = energy(s_runge4, mass, k);
    save(s_runge4, T, "runge4");
    cout << "./bin/01.cpp: (a) 3/3" << endl;

    cout << "./bin/01.cpp: (b) 0/3" << endl;
    // r(0) beliebig, v(0) = 0
    r_0 << 1.4, 0, 0;
    v_0 << 0, 0, 0;
    s_runge4 = rungekutta_4(h, T, r_0, v_0, mass, k);
    s_runge4 = energy(s_runge4, mass, k);
    save(s_runge4, T, "b1");
    cout << "./bin/01.cpp: (b) 1/3" << endl;

    // r(0) beliebig, v(0) beliebig
    r_0 << 1.4, 0, 0;
    v_0 << 0.6, 0, 0;
    s_runge4 = rungekutta_4(h, T, r_0, v_0, mass, k);
    s_runge4 = energy(s_runge4, mass, k);
    save(s_runge4, T, "b2");
    cout << "./bin/01.cpp: (b) 2/3" << endl;

    // r(0) senkrecht v(0)
    r_0 << 1, 0, 0;
    v_0 << 0, 1, 0;
    s_runge4 = rungekutta_4(h, T, r_0, v_0, mass, k);
    s_runge4 = energy(s_runge4, mass, k);
    save(s_runge4, T, "b3");
    cout << "./bin/01.cpp: (b) 3/3" << endl;

<<<<<<< HEAD

<<<<<<< HEAD
>>>>>>> noah
=======
>>>>>>> origin/maxi
=======
>>>>>>> origin/maxi
    return 0;
}
