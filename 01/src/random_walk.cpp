# include <cstdio>
# include <cmath>
# include <random>

int main() {
    int N = 10;
    int Cluster = pow(10, 1);

    int pos_x, pos_y;

    float dir;

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<> dist(0, 1);

    int radii[N];

    for (int i = 0; i < Cluster; i++) {
        pos_x = N/2;
        pos_y = N/2;

        int pos[N][N];

        printf("Walk:\n");
        pos[pos_x][pos_y] = 1;
        for (int i = 1; i <= N; i++) {
            dir = dist(rng);
            if (dir <= 0.25) {
                printf("UP, ");
                pos_y++;
            } else if (dir <= 0.5) {
                printf("LEFT, ");
                pos_x--;
            } else if (dir <= 0.75) {
                printf("DOWN, ");
                pos_y--;
            } else if (dir <= 1) {
                printf("RIGHT, ");
                pos_x++;
            }
            pos[pos_x][pos_y] = 1;
        }
        float r2 = pow(pos_x-N/2, 2) + pow(pos_y-N/2, 2);
        printf("\nEndposition: [%i, %i]\n", pos_x-N/2, pos_y-N/2);
        printf("Radius^2: %f\n", r2);
    }

    return 0;
}
