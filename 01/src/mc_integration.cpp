#include <cmath>
#include <cstdio>
#include <random>

void a(int p) {
    int N = pow(10, p);
    int n = 0;
    double radius_sq;
    double x, y, z;

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<> dist(0, 1);

    for (int i = 0; i < N; i++) {
        x = dist(rng);
        y = dist(rng);
        z = dist(rng);
        /* printf("x: %f, y: %f, z: %f\n", x, y, z); */
        radius_sq = pow(x, 2) + pow(y, 2) + pow(z, 2);
        /* printf("%f\n", radius_sq); */
        if (radius_sq < 1) {
            n++;
        }
    }
    printf("N: %d, ", N);
    printf("n: %d\n", n);

    double pi_est = 8 * (double(n) / double(N));
    double Vol_est = (4./3.) * pi_est;

    double pi = 3.14159;
    double Vol = (4./3.) * pi;

    double Vol_rel_error = (Vol_est - Vol) / Vol * 100;

    printf("Pi estimated: %f\n", pi_est);
    printf("Volumen estimated: %f\n", Vol_est);
    printf("Relativer Fehler Volumen: %f%%\n", Vol_rel_error);
}

int main() {
    a(5);
    return 0;
}

