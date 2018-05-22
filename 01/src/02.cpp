#include <cmath>
#include <cstdio>
#include <random>
#include <array>

// Aufgabenteil a)
void a(int p) {
    printf("Schätzung des Kugelvolumens:\n");
    printf("============================\n");

    // Initialisierung von
    // Anzahl Iterationen N
    // Anzahl der Punkte im Kresi n
    // Radius der Kugel radius_sq
    // Zufallszahlen x, y, z
    const int N = pow(10, p);
    int n = 0;
    double radius_sq;
    double x, y, z;

    // Initialisierung des Random Number Generators
    // nach Anleitung von Übungsblatt 00
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<> dist(0, 1);

    for (int i = 0; i < N; i++) {
        x = dist(rng);
        y = dist(rng);
        z = dist(rng);
        // Berechnung des Radius
        radius_sq = pow(x, 2) + pow(y, 2) + pow(z, 2);
        if (radius_sq < 1) {
            // Zähle, wie viele Zahlentupel innerhalb des Kugelradius liegen
            n++;
        }
    }

    printf("N: %d, ", N);
    printf("n: %d\n", n);

    // Schätze Pi und das Kugelvolumen
    const double pi_est = 6 * (static_cast<double>(n) / static_cast<double>(N));
    const double Vol_est = (4./3.) * pi_est;

    const double pi = 3.14159;
    const double Vol = (4./3.) * pi;

    const double Vol_rel_error = (Vol_est - Vol) / Vol * 100;

    printf("Pi estimated: %f\n", pi_est);
    printf("Volumen estimated: %f\n", Vol_est);
    printf("Relativer Fehler Volumen: %f%%\n", Vol_rel_error);
}

// Aufgabenteil b)
void b() {
    std::array<double, 3> T = {-1., 1.1631, 10000.};
    const double c = 1 / sqrt(3.14159);
    double x0, x1, x2;
    double factor0, factor1, factor2;
    double Integral0, Integral1, Integral2 = 0;

    // Initialisierung des Random Number Generators
    // nach Anleitung von Übungsblatt 00
    std::mt19937 rng;
    rng.seed(std::random_device()());

    std::uniform_real_distribution<> dist0(1./T[0], 0);
    std::uniform_real_distribution<> dist1(0, 1./T[1]);
    std::uniform_real_distribution<> dist2(0, 1./T[2]);

    factor0 = (0 - 1./T[0]) / 1000000000.;
    factor1 = (1./T[1] - 0) / 1000000000.;
    factor2 = (1./T[2] - 0) / 1000000000.;

    for (int j = 0; j < 1000000000; ++j) {
        x0 = dist0(rng);
        x1 = dist1(rng);
        x2 = dist2(rng);
        Integral0 += c * exp(- 1. / (x0 * x0)) * 1. / (x0 * x0);
        Integral1 += - c * exp(- 1. / (x1 * x1)) * 1. / (x1 * x1);
        Integral2 += - c * exp(- 1. / (x2 * x2)) * 1. / (x2 * x2);
    }

    printf("T1: %f,\tI = %f\n", T[0], Integral0*factor0);
    printf("T2: %f,\tI = %f\n", T[1], Integral1*factor1);
    printf("T3: %f,\tI = %f\n", T[2], Integral2*factor2);
}

int main() {
    // a(9);
    b();
    return 0;
}

