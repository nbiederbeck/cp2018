#include <Eigen/Dense>
#include <cmath>
/* #include <solutions.h> */


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
