#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
    int Schritte = pow(10, 1);

    // Erstelle mehrere H
    std::vector<double> h = {-4., -3., -2., -1., 0., 1., 2., 3., 4.};
    double H;

    // wahrscheinlichkeiten fuer die beiden zustaende
    double p1, p2;

    // start und endvektor
    std::vector<double> s0 = {1., 0.};
    std::vector<double> s1 = {0., 0.};
    std::vector<std::vector<double>> M;

    for (int i = 0; i < h.size(); i++) {
        H = h[i];  // weise H zu
        for (int i = 0; i < Schritte; i++) {
            s1 = {0, 0};

            // passe wahrscheinlichkeiten an, jenachdem was H ist
            if (H > 0) {
                p1 = 1;
                p2 = 0;
            } else if (H < 0) {
                p1 = 0;
                p2 = 1;
            } else {
                p1 = 1./2.;
                p2 = 1./2.;
            }

            // erstele metropolis matrix
            M = {{p1, p2},
                 {p1, p2}};

            // matrixmultiplikation
            for (int i = 0; i < s0.size(); i++) {
                for (int j = 0; j < s0.size(); j++){
                    s1[j] += (s0[i] * M[i][j]);
                }
            }

            // schreibe vektoren in die ausgabe
            std::cout << "H = " << H << " :  [ ";
            for (int i = 0; i < s1.size(); i++) {
                std::cout << s1[i] << " " ;
            }
            std::cout << "]" << std::endl;
        }
    }
    return 0;
}
