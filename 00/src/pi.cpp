#include <cstdio>
#include <cstdlib>

int main() {
    double x, y;
    int n, N;

    n = 0;
    N = 100000;

    for (int i = 0; i < N; i++) {
        x = drand48();
        y = drand48();
        if (x * x + y * y < 1) {
            n++;
        }
    }

    double pi_est = 4 * (double)n / (double)N;

    printf("%f\n", pi_est);
    return 0;
}
