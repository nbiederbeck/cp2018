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

    for (int j = 1; j <= Cluster; j++) {
        pos_x = N/2;
        pos_y = N/2;

        int pos[N][N] = {};
        int tries = 0;

        /* printf("walk:\n"); */
        pos[pos_x][pos_y] = 1;
        for (int i = 1; i <= N; i++) {
            if (
                pos[pos_x][pos_y] == 1 &&
                pos[pos_x][pos_y + 1] == 1 &&
                pos[pos_x + 1][pos_y] == 1 &&
                pos[pos_x + 1][pos_y + 1] == 1
            ) {
                printf("BREAK (run %d, iteration %d)\n", j, i);
                break;
            }

            dir = dist(rng);
            if (dir <= 0.25) {
                if (pos[pos_x][pos_y + 1] == 0) {
                    /* printf("up "); */
                    /* printf("(Accepted), "); */
                    pos_y++;
                } else {
                    i--;
                    tries++;
                    /* printf("(Not Accepted), "); */
                    continue;
                }
            } else if (dir <= 0.5) {
                if (pos[pos_x - 1][pos_y] == 0) {
                    /* printf("left "); */
                    /* printf("(Accepted), "); */
                    pos_x--;
                } else {
                    i--;
                    tries++;
                    /* printf("(Not Accepted), "); */
                    continue;
                }
            } else if (dir <= 0.75) {
                if (pos[pos_x][pos_y - 1] == 0) {
                    /* printf("down "); */
                    /* printf("(Accepted), "); */
                    pos_y--;
                } else {
                    i--;
                    tries++;
                    /* printf("(Not Accepted), "); */
                    continue;
                }
            } else if (dir <= 1) {
                if (pos[pos_x + 1][pos_y] == 0) {
                    /* printf("right "); */
                    /* printf("(Accepted), "); */
                    pos_x++;
                } else {
                    i--;
                    tries++;
                    /* printf("(Not Accepted), "); */
                    continue;
                }
            }
            pos[pos_x][pos_y] = 1;
        }
        float r2 = pow(pos_x-N/2, 2) + pow(pos_y-N/2, 2);
        radii[j] = r2;
        /* printf("j: %d\n", j); */
        /* printf("\nendposition: [%i, %i]\n", pos_x-N/2, pos_y-N/2); */
        /* printf("radius^2: %f\n", r2); */
        /* printf("tries: %d\n", tries); */
    }

    return 0;
}
