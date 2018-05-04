
#include <cmath>
#include <random>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>

using namespace std;
// Aufgabenteil a)
void a() {
		// Initialisierung des Random Number Generators
		// nach Anleitung von Übungsblatt 00
		mt19937 rng;
		rng.seed(random_device()());
		uniform_real_distribution<> dist(0, 1);

		vector<double> randcos;
		double x;
		for(int i = 0; i<pow(10,6); i++){
				x = dist(rng);
                // Haenge arcsin(gleichverteilter zufallszahl) hinten an
				randcos.push_back(asin(x));
		}

		uniform_real_distribution<> Dist(-1, 1);
		vector<double> Randcos;
		for(int i = 0; i<pow(10,6); i++){
				x = Dist(rng);
                // Haenge arcsin(gleichverteilter zufallszahl) hinten an
				Randcos.push_back(asin(x));
		}

        // Speicherin in Datei
		ofstream myfile ("./build/task2aI.txt");
		if (myfile.is_open()) {
				for (int i=0; i<randcos.size();i++){
						myfile << randcos[i] << ";" << Randcos[i] << endl;
				}
				myfile.close();
		}

}

void b(float mu, float sigma2){
		mt19937 rng;
		rng.seed(random_device()());
		uniform_real_distribution<> dist(0, 1);

		double U_1 = 0.;
		double U_2 = 0.;
		double Z_1 = 0.;
		double Z_2 = 0.;

		sigma2 = sqrt(sigma2);

        // Speicherin in Datei
		ofstream myfile ("./build/task2b.txt");
		if (myfile.is_open()) {
				for (int i=0; i<pow(10,5); i++){
						U_1 = dist(rng);
						U_2 = dist(rng);

						Z_1 = sqrt(-2.*log(U_1))*cos(2*M_PI*U_2);
						Z_2 = sqrt(-2.*log(U_1))*sin(2*M_PI*U_2);

						Z_1 = mu + Z_1 * sigma2;
						Z_2 = mu + Z_2 * sigma2;
						myfile << Z_1 << ";" << Z_2 << endl;
				}
		}
}

double gauss(double x, double mu, double sigma_squared) {
    double pi = M_PI;
    double g = 1. / sqrt(2. * pi * sigma_squared) * exp( -pow(x - mu, 2.) / (2. * sigma_squared));
    return g;
}

void c(double k, double mu){
        printf("Using k=%.2f.\n", k);
		mt19937 rng;
		rng.seed(random_device()());
		uniform_real_distribution<> dist(0, 1);

		vector<double> exponential;
        vector<double> uniform_exp;
        vector<double> gauss_rnd_x;
        vector<double> gauss_rnd_y;

		double x;
        double y;
        double N = pow(10, 6);


		for(int i = 0; i<N; i++){
				x = dist(rng);
                // Haenge -log(gleichverteilter zufallszahl) hinten an
				exponential.push_back(-log(x));

                // Ziehe gleichverteilte Zufallszahl zwischen
                // 0..(k * Exponentialfkt)
                uniform_real_distribution<> exp_dist(0., k * exp(-exponential[i]));
                y = exp_dist(rng);
                uniform_exp.push_back(y);
		}

		for(int i = 0; i < exponential.size(); i++){
                // wenn kleiner als Gauss, haenge an
                // sowohl x als auch y wert in neue arrays
                if (uniform_exp[i] < gauss(exponential[i], 0., 1.)){
                    gauss_rnd_y.push_back(uniform_exp[i]);

                    gauss_rnd_x.push_back(exponential[i]);
                }
        }

        for (int i = 0; i < exponential.size(); ++i) {
            // negative Zufallszahlen, exponentialverteilt
            if (i % 2 == 0) {
                exponential[i] *= -1.;
            }
            // verschiebe zufallszahlen um mu=3
            exponential[i] += mu;
        }
        for (int i = 0; i < gauss_rnd_x.size(); ++i) {
            // wie oben
            if (i % 2 == 0) {
                gauss_rnd_x[i] *= -1.;
            }
            gauss_rnd_x[i] += mu;
        }

        // Speicherin in Datei
		ofstream myfile ("./build/task2c.txt");
		if (myfile.is_open()) {
				for (int i=0; i < exponential.size(); i++){
						myfile
                            << exponential[i] << ";"
                            << uniform_exp[i] << endl;
				}
				myfile.close();
		}

        // Speicherin in Datei
		ofstream myfile2 ("./build/task2cI.txt");
		if (myfile2.is_open()) {
				for (int i=0; i < gauss_rnd_x.size(); i++){
						myfile2
                            << gauss_rnd_x[i] << ";"
                            << gauss_rnd_y[i] << endl;
				}
				myfile2.close();
		}

}

int main() {
        cout << "Aufgabe 2" << endl;
        cout << "=========" << endl;

        cout << "a)" << endl;
        cout << "--" << endl;
        a();

        cout << "b)" << endl;
        cout << "--" << endl;
        b(3., 4.);

        cout << "c)" << endl;
        cout << "--" << endl;
        c(0.7, 3);
}
