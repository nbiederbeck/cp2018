# include <cstdio>
# include <cmath>
# include <random>
# include <fstream>

int main() {
    std::fstream fs;
    fs.open("build/data.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    fs << "# N mean_r\n";

    // Anzahl Wege
    int Cluster = 100000;

    int pos_x, pos_y;

    // Startwert im Gitter
    int start = 30;

    double dir;

    // Random Numbers nach Anleitung
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<> dist(0, 1);


    // Iteration über Weglängen
    for (int N = 10; N <= 60; N+=5) {
        double radii[100000] = {};

        // Anzahl Sackgassen
        int breaks = 0;

        // Iteration über Anzahl Wege
        for (int j = 0; j < Cluster; j++) {
            // Setze den Startwert auf die Mitte des Gitters
            pos_x = start;
            pos_y = start;

            int pos[60][60] = {};
            int tries = 0;

            pos[start][start] = 1;
            for (int i = 0; i < N; i++) {
                // Random Walk!
                if (
                    // Bei einer Sackgasse, brich ab
                    pos[pos_x][pos_y + 1] == 1 &&
                    pos[pos_x + 1][pos_y] == 1 &&
                    pos[pos_x][pos_y - 1] == 1 &&
                    pos[pos_x - 1][pos_y] == 1
                ) {
                    /* printf("BREAK (Weglänge %d, Weg %d, Schritt %d)\n", N, j, i); */
                    breaks++;
                    break;
                }

                // Zu laufende Richtung zwischen 0..1
                // Aufteilen nach Vierteln
                dir = dist(rng);
                if (dir <= 0.25) { // Hoch
                    // Schritt nur annehmen, wenn Feld noch frei
                    if (pos[pos_x][pos_y + 1] == 0) {
                        pos_y++;
                    } else { // Ansonsten nochmal versuchen
                        i--;
                        tries++;
                        continue;
                    }
                } else if (dir <= 0.5) { // Links
                    if (pos[pos_x - 1][pos_y] == 0) {
                        pos_x--;
                    } else {
                        i--;
                        tries++;
                        continue;
                    }
                } else if (dir <= 0.75) { // Runter
                    if (pos[pos_x][pos_y - 1] == 0) {
                        pos_y--;
                    } else {
                        i--;
                        tries++;
                        continue;
                    }
                } else if (dir <= 1) { // Rechts
                    if (pos[pos_x + 1][pos_y] == 0) {
                        pos_x++;
                    } else {
                        i--;
                        tries++;
                        continue;
                    }
                }
                // Markiere Feld als schon gelaufen
                pos[pos_x][pos_y] = 1;
            }

            double r2 = pow(pos_x - start, 2) + pow(pos_y - start, 2);
            radii[j] = sqrt(r2);
        }
        printf("Anzahl Sackgassen bei Weglänge %d: %d/%d\n", N, breaks, Cluster);

        float sum = 0;
        for (int i = 0; i < Cluster; i++) {
            sum += radii[i];
        }

        float mean = sum/double(Cluster);


        fs << N << " "
           << mean << "\n";


        printf("Mittlere Entfernung von [0,0]: %f\n", mean);
    }

    fs.close();

    return 0;
}
