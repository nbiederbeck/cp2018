#include <Eigen/Dense>
#include <cmath>
/* #include <solutions.h> */


Eigen::VectorXd three_body_force(
    Eigen::VectorXd r1, double m1,
    Eigen::VectorXd r2, double m2,
    double G)
{
    double m_sun = 1.;
    Eigen::VectorXd r = r2 - r1;
    /* m2 = 0; */
    return - G * (- m1 * m2 * r / std::pow(r.norm(), 3) + m1 * m_sun * r1 / std::pow(r1.norm(), 3));
}


struct solutions rungekutta_moon(
    double h,
    int T,
    Eigen::VectorXd r_0_planet,
    Eigen::VectorXd v_0_planet,
    Eigen::VectorXd r_0_moon,
    Eigen::VectorXd v_0_moon,
    double mass_planet,
    double mass_moon,
    double G)
{

    // planet
    Eigen::MatrixXd r_i_planet = r_0_planet;
    Eigen::MatrixXd v_i_planet = v_0_planet;
    Eigen::VectorXd r_n_planet(r_0_planet.rows());
    Eigen::VectorXd v_n_planet(r_0_planet.rows());

    // moon
    Eigen::MatrixXd r_i_moon = r_0_moon;
    Eigen::MatrixXd v_i_moon = v_0_moon;
    Eigen::VectorXd r_n_moon(r_0_moon.rows());
    Eigen::VectorXd v_n_moon(r_0_moon.rows());

    Eigen::VectorXd k1(r_0_planet.rows());
    Eigen::VectorXd k2(r_0_planet.rows());
    Eigen::VectorXd k3(r_0_planet.rows());
    Eigen::VectorXd k4(r_0_planet.rows());

    for(int i = 0; i < T / h; i++){
        // init help var

        // planet
        Eigen::MatrixXd join_r_planet(r_i_planet.rows(), r_i_planet.cols()+1);
        Eigen::MatrixXd join_v_planet(r_i_planet.rows(), r_i_planet.cols()+1);

        // moon
        Eigen::MatrixXd join_r_moon(r_i_moon.rows(), r_i_moon.cols()+1);
        Eigen::MatrixXd join_v_moon(r_i_moon.rows(), r_i_moon.cols()+1);

        // physics
        // planet
        k1 = h * three_body_force(r_i_planet.col(i), mass_planet, r_i_moon.col(i), mass_moon, G) / mass_planet;
        k2 = h * three_body_force(r_i_planet.col(i) + 0.5 * k1, mass_planet, r_i_moon.col(i) + 0.5 * k1, mass_moon, G) / mass_planet;
        k3 = h * three_body_force(r_i_planet.col(i) + 0.5 * k2, mass_planet, r_i_moon.col(i) + 0.5 * k2, mass_moon, G) / mass_planet;
        k4 = h * three_body_force(r_i_planet.col(i) + 1.0 * k3, mass_planet, r_i_moon.col(i) + 1.0 * k3, mass_moon, G) / mass_planet;
        v_n_planet << v_i_planet.col(i) + 1./6. * (k1 + 2 * k2 + 2 * k3 + k4);

        k1 = h * v_i_planet.col(i);
        k2 = h * (v_i_planet.col(i) + 0.5 * k1);
        k3 = h * (v_i_planet.col(i) + 0.5 * k2);
        k4 = h * (v_i_planet.col(i) + 1.0 * k3);
        r_n_planet << r_i_planet.col(i) + 1./6. * (k1 + 2 * k2 + 2 * k3 + k4);

        // moon
        k1 = h * three_body_force(r_i_moon.col(i), mass_moon, r_i_planet.col(i), mass_planet, G) / mass_moon;
        k2 = h * three_body_force(r_i_moon.col(i) + 0.5 * k1, mass_moon, r_i_planet.col(i) + 0.5 * k1, mass_planet, G) / mass_moon;
        k3 = h * three_body_force(r_i_moon.col(i) + 0.5 * k2, mass_moon, r_i_planet.col(i) + 0.5 * k2, mass_planet, G) / mass_moon;
        k4 = h * three_body_force(r_i_moon.col(i) + 1.0 * k3, mass_moon, r_i_planet.col(i) + 1.0 * k3, mass_planet, G) / mass_moon;
        v_n_moon << v_i_moon.col(i) + 1./6. * (k1 + 2 * k2 + 2 * k3 + k4);

        k1 = h * v_i_moon.col(i);
        k2 = h * (v_i_moon.col(i) + 0.5 * k1);
        k3 = h * (v_i_moon.col(i) + 0.5 * k2);
        k4 = h * (v_i_moon.col(i) + 1.0 * k3);
        r_n_moon << r_i_moon.col(i) + 1./6. * (k1 + 2 * k2 + 2 * k3 + k4);

        // fill old var with new values
        // planet
        join_r_planet << r_i_planet, r_n_planet;
        r_i_planet = join_r_planet;
        join_v_planet << v_i_planet, v_n_planet;
        v_i_planet = join_v_planet;

        // moon
        join_r_moon << r_i_moon, r_n_moon;
        r_i_moon = join_r_moon;
        join_v_moon << v_i_moon, v_n_moon;
        v_i_moon = join_v_moon;

    }
    solutions sol;
    // planet
    sol.r_i = r_i_planet; sol.v_i = v_i_planet;
    // moon
    sol.r_i_moon = r_i_moon; sol.v_i_moon = v_i_moon;
    return sol;
}
