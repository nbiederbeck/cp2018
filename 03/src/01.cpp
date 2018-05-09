#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <random>
#include <fstream>

int main(int argc, char *argv[])
{
    int Schritte = pow(10, 5);

    // Erstelle mehrere H
    std::vector<double> h = {-5., -4., -3., -2., -1., 0., 1., 2., 3., 4.};
    double H;
    int anzahl_H = pow(10, 4);

    // wahrscheinlichkeiten fuer die beiden zustaende
    double p1, p2;

    // start und endvektor
    std::vector<double> s0;
    std::vector<double> s1 = {0., 0.};
    std::vector<std::vector<double>> M;

    // Random Numbers
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<double> dist(-5., 5.);

    std::cout << "Magnetfeld: Wahrscheinlichkeiten Spin = [1 -1]" << std::endl;
    std::ofstream myfile ("./build/01_b.txt");
    myfile << "# H p(s=1) p(s=-1)" << std::endl;
    for (int i = 0; i < anzahl_H; i++) {
        // H = h[i];  // weise H zu
        H = dist(rng);
        s0 = {1., 0.};
        // s0 = {0., 1.};

        // passe wahrscheinlichkeiten an, jenachdem was H ist
        p1 = pow(2.71, H) / (pow(2.71, H) + pow(2.71, -H));
        p2 = pow(2.71, -H) / (pow(2.71, H) + pow(2.71, -H));

        // erstelle metropolis matrix
        M = {{p1, p2},
             {p1, p2}};

        for (int i = 0; i < Schritte; i++) {
            s1 = {0, 0};

            // matrixmultiplikation
            for (int i = 0; i < s0.size(); i++) {
                for (int j = 0; j < s0.size(); j++){
                    s1[i] += (s0[j] * M[j][i]);
                }
            }

            s0 = s1;

        }

        // ausgabe
        if (myfile.is_open()) {
            std::cout << "H = " << H << " :  [ ";
            myfile << H << ",";
            for (int i = 0; i < s1.size(); i++) {
                std::cout << s1[i] << " " ;  // terminal
                myfile << s1[i] << ","; // file
            }
            std::cout << "]" << std::endl;
            myfile << std::endl;
        }
    }
    myfile.close();
    return 0;
}
