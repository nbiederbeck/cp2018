
#include <cmath>
#include <random>
#include <iostream>
#include <vector>
#include <fstream>

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
				randcos.push_back(asin(x));
		}

		uniform_real_distribution<> Dist(-1, 1);
		vector<double> Randcos;
		for(int i = 0; i<pow(10,6); i++){
				x = Dist(rng);
				Randcos.push_back(asin(x));
		}

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



int main() {
		cout << "Aufgabe 2" << endl;
		cout << "=========" << endl;

		cout << "a)" << endl;
		cout << "--" << endl;
		a();

		cout << "b)" << endl;
		cout << "--" << endl;
		b(3., 4.);
}
