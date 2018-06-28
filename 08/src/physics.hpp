#include <Eigen/Dense>

// Euler Verfahren
Eigen::Vector4d euler(Eigen::Vector4d state, double h)
{
    double g = 1.0;
    Eigen::Vector4d next;

    next(0) = state(0) + h * state(2);
    next(1) = state(1) + h * state(3);
    next(2) = state(2) + h * 2.0 * g * (state(1) - 2.0 * state(0));
    next(3) = state(3) + h * 2.0 * g * (state(0) - 1.0 * state(1));

    return next;
}

// Vektorielle Funktion f, die im Runge Kutta Verfahren benetigt wird
Eigen::Vector4d f(
    Eigen::Vector4d state,
    double m1=1.0,
    double m2=1.0,
    double L1=1.0,
    double L2=1.0,
    double g=9.81)
{
    Eigen::Vector4d temp;


    temp(0) = state(2);  // Erster Eintrag ist Este Ableitung, also dritter Eintrag
    temp(1) = state(3);
    // Dritter Eintrag ist zweite Ableitung

    double mu = m2 / (m1 + m2);
    double lambda = L1 / L2;
    double g1 = g / L1;
    double g2 = g / L2;

    // Kurzschreibweisen
    double t1 = state(0);
    double t2 = state(1);
    double sin_t1 = std::sin(t1);
    double sin_t2 = std::sin(t2);
    double cos_t1 = std::cos(t1);
    double cos_t2 = std::cos(t2);
    double sin_t2_t1 = std::sin(t2 - t1);
    double cos_t2_t1 = std::cos(t2 - t1);

    double f = 1.0 / (1.0 - mu * std::pow(cos_t2_t1, 2));  // Vorfaktor, bei beiden gleich

    temp(2) = f * (
              mu * g1 * sin_t2 * cos_t2_t1
              + mu * std::pow(state(2), 2) * sin_t2_t1 * cos_t2_t1
              - g1 * sin_t1
              + (mu / lambda) * std::pow(state(3), 2) * sin_t2_t1
              );
    temp(3) = f * (
              g2 * sin_t1 * cos_t2_t1
              - mu * std::pow(state(3), 2) * sin_t2_t1 * cos_t2_t1
              - g2 * sin_t2
              - mu * std::pow(state(2), 2) * sin_t2_t1
              );

    return temp;
}

// Runge-Kutta Verfahren
Eigen::Vector4d rungekutta(
    Eigen::Vector4d state,
    double h)
{
    Eigen::Vector4d k1 = h * f(state);
    Eigen::Vector4d k2 = h * f(state + 0.5 * k1);
    Eigen::Vector4d k3 = h * f(state + 0.5 * k2);
    Eigen::Vector4d k4 = h * f(state + k3);

    return state + 1.0 / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
}

// Potentielle Energie
double Epot(
    Eigen::Vector4d state,
    double m1=1.0,
    double m2=1.0,
    double L1=1.0,
    double L2=1.0,
    double g=9.81)
{
    // Umschreiben in orthogonale Koordinaten
    // double x1 = L1 * std::sin(state(0));  // theta_1
    double y1 = L1 * std::cos(state(0));  // theta_1
    // double x2 = x1 + L2 * std::sin(state(1));  // theta_2
    double y2 = y1 + L2 * std::cos(state(1));  // theta_2

    double E = m1 * g * (L1 - y1) + m2 * g * (L1 + L2 - y2);
    return E;
}

// Kinetische Energie
double Ekin(
    Eigen::Vector4d state,
    double m1=1.0,
    double m2=1.0,
    double L1=1.0,
    double L2=1.0,
    double g=9.81)
{
    // Umschreiben in orthogonale Koordinaten
    double x1 = L1 * std::cos(state(0)) * state(2);  // theta_1
    double y1 = L1 * std::sin(state(0)) * state(2);  // theta_1
    double x2 = x1 + L2 * std::cos(state(1)) * state(3);  // theta_2
    double y2 = y1 + L2 * std::sin(state(1)) * state(3);  // theta_2

    double E = m1 / 2.0 * (x1 * x1 + y1 * y1) + m2 / 2.0 * (x2 * x2 + y2 * y2);
    return E;
}
