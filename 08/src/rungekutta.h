#include <Eigen/Dense>
#include <cmath>
/* #include <solutions.h> */


struct pendulum rungekutta(double h, int T, Eigen::VectorXd r_0, Eigen::VectorXd v_0, double mass, double k)
{
    Eigen::MatrixXd theta = r_0;
    Eigen::MatrixXd theta_ = v_0;

    Eigen::VectorXd r_n(r_0.rows());
    Eigen::VectorXd v_n(r_0.rows());

    Eigen::VectorXd k1(r_0.rows());
    Eigen::VectorXd k2(r_0.rows());
    Eigen::VectorXd k3(r_0.rows());
    Eigen::VectorXd k4(r_0.rows());

    for(int i = 0; i < T / h; i++){
        // init help var
        Eigen::MatrixXd joined_r_i(theta.rows(), theta.cols()+1);
        Eigen::MatrixXd joined_v_i(theta.rows(), theta.cols()+1);

        // physics
        k1 = h * force(theta.col(i), k) / mass;
        k2 = h * force(theta.col(i) + 0.5 * k1, k) / mass;
        k3 = h * force(theta.col(i) + 0.5 * k2, k) / mass;
        k4 = h * force(theta.col(i) + 1.0 * k3, k) / mass;
        v_n << theta_.col(i) + 1./6. * (k1 + 2 * k2 + 2 * k3 + k4);

        k1 = h * theta_.col(i);
        k2 = h * (theta_.col(i) + 0.5 * k1);
        k3 = h * (theta_.col(i) + 0.5 * k2);
        k4 = h * (theta_.col(i) + 1.0 * k3);
        r_n << theta.col(i) + 1./6. * (k1 + 2 * k2 + 2 * k3 + k4);

        // fill old var with new values
        joined_r_i << theta, r_n;
        theta = joined_r_i;
        joined_v_i << theta_, v_n;
        theta_ = joined_v_i;
    }
    pendulum s_euler ;
    s_euler.theta = theta; s_euler.theta_ = theta_;
    return s_euler;
}
