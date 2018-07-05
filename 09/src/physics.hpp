// vim: commentstring=//%s expandtab shiftwidth=4
#include <Eigen/Dense>

using std::pow;
using std::sqrt;

// Lennard Jones Potential
double pot(Eigen::Vector4d state)
{
    double rx = state(0);
    double ry = state(1);
    double r = sqrt(pow(rx, 2) + pow(ry, 2));
    double V = 4.0 * (
        + pow((1.0 / r), 12)
        - pow((1.0 / r), 6)
    );
    return V;
}

// Kraftfeld zur Berechnung von \vec{a}
Eigen::Vector2d force(Eigen::Vector2d r, double m=1.0)
// {
//     Eigen::Vector2d F = {
//         - 4.0 * (- 12.0 * pow(r(0), -13) + 6.0 * pow(r(0), -7)),
//         - 4.0 * (- 12.0 * pow(r(1), -13) + 6.0 * pow(r(1), -7)),
//     };
//     return F / m;
// }


// 4d-Vektor fur 2d Radius + 2d Geschwindigkeit
// Hier gibt es sicherlich eine besser Methode,
// die Matrixmultiplikation verwendet
Eigen::MatrixXd verlet(Eigen::MatrixXd now, Eigen::MatrixXd last, double h=0.01)
{
    // // Split r and v
    // Eigen::Vector2d r_now = {now(0), now(1)};
    // Eigen::Vector2d v_now = {now(2), now(3)};
    // Eigen::Vector2d r_last = {last(0), last(1)};
    // Eigen::Vector2d v_last = {last(2), last(3)};

    // Eigen::Vector2d a = force(r_now);

    // Eigen::Vector2d r_next = {0.0, 0.0};
    // r_next = 2.0 * r_now - r_last + a * pow(h, 2);

    // Eigen::Vector2d v_next = {0.0, 0.0};
    // v_next = 1.0 / (2.0 * h) * (r_next - r_last);

    // Eigen::Vector4d next = {r_next(0), r_next(1), v_next(0), v_next(1)};

    // return next;
    return now;
}
