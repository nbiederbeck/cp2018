#include <Eigen/Dense>
#include <cmath>
/* #include <solutions.h> */


struct solutions rungekutta(double h, int T, Eigen::VectorXd r_0, Eigen::VectorXd v_0, double mass, double k)
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
