// vim: commentstring=//%s expandtab shiftwidth=4
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>
#include <ctime>
#include <vector>


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
        // cout << "=========i: " << i << " ==============" <<endl;
        // cout << "Stepsize: " << t_i[i] << " - " << t_i[i-1] << " = " << stepsize(t_i,i) <<endl;
        // cout << "t_i: " << t_i[i] <<endl;
        // cout << "r_i: " << r_i[i] <<endl;
        // cout << "r_i.back: " << r_i[i-1] <<endl;
        // cout << "v_i: " << v_i[i] <<endl;
        // cout << "v_i.back: " << v_i[i-1] <<endl;
    }
    solutions s_euler ;
    s_euler.r_i = r_i;
    s_euler.v_i = v_i;
    return s_euler;
}

int main(int argc, char *argv[])
{

    double t_0 = 0;
    double T = 16.;
    int h = 20000;

    vector<double> t_i = diskretisierung(t_0, T, h);
    struct solutions s_euler = euler(t_i, 0, 1);

    std::ofstream file ("build/euler.txt");
    
    for(unsigned i = 0; i< s_euler.r_i.size(); ++i) {
        file << s_euler.r_i[i] << "; " << s_euler.v_i[i] << std::endl;
    }
    
    return 0;
}
