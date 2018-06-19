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
using Eigen::VectorXf;
using Eigen::MatrixXf;

vector<double> diskretisierung(double t_0, double T, int h){
    vector<double> t = {t_0};
    for(int i=1; i<=h; i++){
        t.push_back(t_0 + T/h * i);
    }
    return t;
}

double stepsize(vector<double> t, int i){
    return t[i] - t[i-1];
}

struct solutions {
    MatrixXf r_i;
    MatrixXf v_i;
};

VectorXf func(double t, VectorXf x_i){
    // die funktion haengt explizit nicht von t ab
    double omega = 1.;

    return pow(omega,2) * x_i;
}

// VectorXf stepk

struct solutions euler(vector<double> t_i, VectorXf r_0, VectorXf v_0){
    MatrixXf r_i = r_0;
    MatrixXf v_i = v_0;

    int r = r_i.rows();
    VectorXf r_n(r);
    VectorXf v_n(r);

    for(int i=1; i<t_i.size(); i++){
        // init help var
        MatrixXf joined_r_i(r, i+1);
        MatrixXf joined_v_i(r, i+1);

        // physics
        r_n << r_i.col(i-1) - stepsize(t_i,i) * func(t_i[i], v_i.col(i-1)); 
        v_n << v_i.col(i-1) + stepsize(t_i,i) * func(t_i[i], r_i.col(i-1)); 
       
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

struct solutions runge_kutta_2(vector<double> t_i, VectorXf r_0, VectorXf v_0){
    MatrixXf r_i = r_0;
    MatrixXf v_i = v_0;

    int r = r_i.rows();
    VectorXf r_n(r);
    VectorXf v_n(r);

    for(int i=1; i<t_i.size(); i++){
        // init help var
        MatrixXf joined_r_i(r, i+1);
        MatrixXf joined_v_i(r, i+1);

        // physics
        r_n << r_i.col(i-1) - stepsize(t_i,i) * func(t_i[i], v_i.col(i-1)); 
        v_n << v_i.col(i-1) + stepsize(t_i,i) * func(t_i[i], r_i.col(i-1)); 
       
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
    double T = 100.;
    int h = 20000;
    int dim = 3;

    // initaliziere Startvektoren
    VectorXf r_0(dim);
    VectorXf v_0(dim);
    r_0 << 1, 0, 0;
    v_0 << 0, 0, 0;

    // euler solution
    vector<double> t_i = diskretisierung(t_0, T, h);
    struct solutions s_euler = euler(t_i, r_0, v_0);
    save(s_euler, T, "euler");

    
    return 0;
}
