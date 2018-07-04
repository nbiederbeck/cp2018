#include <Eigen/Dense>


struct solutions {
    Eigen::MatrixXd r_i;
    Eigen::MatrixXd v_i;
    Eigen::MatrixXd r_i_moon;
    Eigen::MatrixXd v_i_moon;
    Eigen::VectorXd energy;
    Eigen::VectorXd momentum;
};
