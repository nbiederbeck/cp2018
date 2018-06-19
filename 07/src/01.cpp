// vim: commentstring=//%s expandtab shiftwidth=4
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;

vector<double> diskretisierung(double t_0, double T, int h){
    vector<double> t = {t_0};
    for(int i=1; i<=h; i++){
        t.push_back(t_0 + T/h * i);
    }
    return t;
}

double stepsize(vector<double> t, int i){
    return t[i+1] - t[i];
}

struct solutions {
    Eigen::MatrixXd r_i;
    Eigen::MatrixXd v_i;
};

Eigen::VectorXd func(double t, Eigen::VectorXd x_i){
    // die funktion haengt explizit nicht von t ab
    double omega = 1;

    return pow(omega,2) * x_i;
}

Eigen::VectorXd force(Eigen::VectorXd r) {
    double k = 1.;
    return -k * r;
}


struct solutions euler(double h, int T, Eigen::VectorXd r_0, Eigen::VectorXd v_0){
    Eigen::MatrixXd r_i = r_0;
    Eigen::MatrixXd v_i = v_0;

    Eigen::VectorXd r_n(r_0.rows());
    Eigen::VectorXd v_n(r_0.rows());

    for(int i = 0; i < T / h; i++){
        Eigen::MatrixXd joined_r_i(r_i.rows(), r_i.cols()+1);
        Eigen::MatrixXd joined_v_i(r_i.rows(), r_i.cols()+1);

        // physics
        v_n << v_i.col(i) + h * force(r_i.col(i));
        r_n << r_i.col(i) + h * v_n;

        // fill old var with new values
        joined_r_i << r_i, r_n;
        r_i = joined_r_i;
        joined_v_i << v_i, v_n;
        v_i = joined_v_i;
    }
    solutions eul;
    eul.r_i = r_i; eul.v_i = v_i;
    return eul;
}

struct solutions rungekutta_2(double h, int T, Eigen::VectorXd r_0, Eigen::VectorXd v_0) {
    Eigen::MatrixXd r_i = r_0;
    Eigen::MatrixXd v_i = v_0;

    Eigen::VectorXd r_n(r_0.rows());
    Eigen::VectorXd v_n(r_0.rows());

    Eigen::VectorXd k1(r_0.rows());
    Eigen::VectorXd k2(r_0.rows());

    for (int i = 0; i < T / h; i++) {
        Eigen::MatrixXd joined_r_i(r_i.rows(), r_i.cols()+1);
        Eigen::MatrixXd joined_v_i(r_i.rows(), r_i.cols()+1);

        // physics
        // v, y_1
        k1 = h * force(r_i.col(i));
        k2 = h * force(r_i.col(i) + 0.5 * k1);
        v_n << v_i.col(i) + k2;
        // r, y_0
        k1 = h * v_n;
        k2 = h * (v_n + 0.5 * k1);
        r_n << r_i.col(i) + k2;

        // fill old var with new values
        joined_r_i << r_i, r_n;
        r_i = joined_r_i;
        joined_v_i << v_i, v_n;
        v_i = joined_v_i;
    }
    solutions rk2;
    rk2.r_i = r_i; rk2.v_i = v_i;
    return rk2;
}

struct solutions runge_kutta_4(vector<double> t_i, Eigen::VectorXd r_0, Eigen::VectorXd v_0){
    Eigen::MatrixXd r_i = r_0;
    Eigen::MatrixXd v_i = v_0;

    int r = r_i.rows();
    Eigen::VectorXd r_n(r);
    Eigen::VectorXd v_n(r);

    Eigen::VectorXd k_1(r);
    Eigen::VectorXd k_2(r);
    Eigen::VectorXd k_3(r);
    Eigen::VectorXd k_4(r);

    for(int i=1; i<t_i.size(); i++){
        // init help var
        Eigen::MatrixXd joined_r_i(r, i+1);
        Eigen::MatrixXd joined_v_i(r, i+1);

        // physics
        k_1 << func(t_i[i], v_i.col(i-1));
        k_2 << func(t_i[i] + 1./2* stepsize(t_i,i), v_i.col(i-1) + stepsize(t_i,i)*1./2*k_1);
        k_3 << func(t_i[i] + 1./2* stepsize(t_i,i), v_i.col(i-1) + stepsize(t_i,i)*1./2*k_2);
        k_4 << func(t_i[i] + 2./2* stepsize(t_i,i), v_i.col(i-1) + stepsize(t_i,i)*2./2*k_3);
        r_n << r_i.col(i-1) - stepsize(t_i,i) * (1./6 * k_1 + 1./3 * k_2 + 1./3 * k_3 + 1./6 * k_4);

        k_1 << func(t_i[i], r_i.col(i-1));
        k_2 << func(t_i[i] + 1./2* stepsize(t_i,i), r_i.col(i-1) +stepsize(t_i,i)*1./2*k_1);
        k_3 << func(t_i[i] + 1./2* stepsize(t_i,i), r_i.col(i-1) +stepsize(t_i,i)*1./2*k_2);
        k_4 << func(t_i[i] + 2./2* stepsize(t_i,i), r_i.col(i-1) +stepsize(t_i,i)*2./2*k_3);
        v_n << v_i.col(i-1) + stepsize(t_i,i) * (1./6 * k_1 + 1./3 * k_2 + 1./3 * k_3 + 1./6 * k_4);

        // fill old var with new values
        joined_r_i << r_i, r_n;
        r_i = joined_r_i;
        joined_v_i << v_i, v_n;
        v_i = joined_v_i;
    }
    solutions s_euler ;
    s_euler.r_i = r_i; s_euler.v_i = v_i;
    return s_euler;
}

void save(struct solutions sol, double T, const std::string &filename){
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
}


int main(int argc, char *argv[])
{

    // setze Start/Rand-bedingugen
    double t_0 = 0;
    double T = 20. * M_PI;
    double h = M_PI / 100.;
    const int dim = 3;

    // initaliziere Startvektoren
    Eigen::VectorXd r_0(dim);
    Eigen::VectorXd v_0(dim);
    r_0 << 1, 0, 0;
    v_0 << 0, 0, 0;

    // euler solution
    struct solutions s_euler = euler(h, T, r_0, v_0);
    save(s_euler, T, "euler");

    struct solutions s_runge = rungekutta_2(h, T, r_0, v_0);
    save(s_runge, T, "runge");

    return 0;
}
