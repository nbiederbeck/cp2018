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

vector<double> euler(vector<double> t_i, double y_0){
    vector<double> y_i = {y_0};
    for(int i=1; i<=t_i.size(); i++){
        y_i.push_back(
                y_i.back() + stepsize(t_i,i) * func(y_i.back())
                );
        cout << "=========i: " << i << " ==============" <<endl;
        cout << "Stepsize: " << stepsize(t_i,i) <<endl;
        cout << "t_i: " << t_i[i] <<endl;
        cout << "y_i: " << y_i[i] <<endl;
    }
    return y_i;
}

int main(int argc, char *argv[])
{

    double t_0 = 0;
    double T = 10.;
    int h = 10;

    vector<double> t_i = diskretisierung(t_0, T, h);
    t_i = euler(t_i, 1);

    for(unsigned i = 0; i< t_i.size(); ++i) {
        std::cout << t_i[i] << std::endl;
    }
    return 0;
}
