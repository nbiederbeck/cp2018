#include <cmath>
#include <cstdio>
#include <random>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    // start values
    double s = -1.;
    const double s_up = 1.;
    const double s_down = -1.;
    double H = 1.;
    double beta = 1.;
    const double e = M_E;
    double E = - s * H;

    const double Schritte = pow(10, 4);
    const double anzahl_H = pow(10, 3);

    // Random Numbers
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<double> dist_normal(0., 1.);
    std::uniform_real_distribution<double> dist_H(-5., 5.);

    // Prepare output file
    std::ofstream myfile ("./build/01_b.txt");
    myfile << "# H p(s=1) p(s=-1)" << std::endl;

    // initialize propabilities
    double p_up, p_down, p_sum;

    std::cout << "Loop over " << anzahl_H << " magnetic fields"
              << " a " << Schritte << " steps." << std::endl;
    for (int i = 0; i < anzahl_H; i++) {
        // chose random magnetic field
        H = dist_H(rng);
        std::cout << H << " ";
        // chose random initial spin
        if (dist_normal(rng) < 0.5) {
            s = 1.;
        } else {
            s = -1.;
        }

        for (int j = 0; j < Schritte; j++) {

            // recalculate propability for given magnetic field and current
            // spin
            p_sum = pow(e, beta * H * (s_up - s)) + pow(e, beta * H * (s_down - s));
            p_up = pow(e, beta * H * (s_up - s)) / p_sum;
            p_down = pow(e, beta * H * (s_down - s)) / p_sum;

            // recalculate spin given propability (up/down)
            // also randomly flip spin, the higher the field the lower
            // the propability to flip randomly
            if (p_up > p_down) {
                s = 1.;
                if (dist_normal(rng) > p_up) {
                    s *= -1;
                }
            } else if (p_up < p_down) {
                s = -1.;
                if (dist_normal(rng) > p_down) {
                    s *= -1;
                }
            } else { // (p_up == p_down) only random spin flip
                if (dist_normal(rng) > 0.5) {
                    s *= -1;
                }
            }

        }

        // output to file
        if (myfile.is_open()) {
            myfile << H << ",";
            myfile << p_up - p_down << ",";
            myfile << p_down << ",";
            myfile << std::endl;
        }

    }

    return 0;
}
