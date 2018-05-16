#include <cmath>
#include <cstdio>
#include <random>
#include <fstream>
#include <iostream>

using namespace std;

int n = 100;
int m = n;
int n_sweeps = 1010;

mt19937 rng;
// rng.seed(std::random_device()());
uniform_real_distribution<double> random_uniform(0, 1);

uniform_real_distribution<double> random_n(1, n+1);
uniform_real_distribution<double> random_m(1, m+1);


// initialize lattice
int** init_lattice(int m, int n) {
		mt19937 rng;
		rng.seed(std::random_device()());
		discrete_distribution<> random_choice({1, 1});

		// init (n+2)x(m+2) lattice
		int **lattice;
		lattice = new int*[m + 2];
		for (int i = 0; i < m + 2; ++i)
				lattice[i] = new int[n + 2];

		// Assign rnadom spin values
		for(int x = 1; x < m + 1; ++x) {
				for(int y = 1; y < n + 1; ++y) {
						if(random_choice(rng) == 0) {
								lattice[x][y] = -1;
						}
						else{
								lattice[x][y] = 1;
						}
				}
		}
		return lattice;
}

// make lattice periodic
int** periodic_lattice(int** lattice, int m, int n) {
		for(int i = 1; i < m + 1; ++i) {
				lattice[0][i] = lattice[m][i];
				lattice[m+1][i] = lattice[1][i];
		}
		for(int i = 1; i < n + 1; ++i) {
				lattice[i][0] = lattice[i][n];
				lattice[i][n+1] = lattice[i][1];
		}
		return lattice;
}

// perform one sweep a nxm possible spin flips
int** sweep(int** lattice, double beta, int* Energie, int* Sum_Spins, int m, int n) {
		int i, j;

		for (int k = 0; k < (n * m); ++k) {
				i = static_cast<int>(random_n(rng));
				j = static_cast<int>(random_m(rng));

				int Energy = -lattice[i][j] * (
								lattice[i][j - 1]
								+ lattice[i][j + 1]
								+ lattice[i - 1][j]
								+ lattice[i + 1][j]
								);
				*Energie += Energy;

				if(-2 * Energy < 0) {
						lattice[i][j] *= -1;
				}
				else if(exp(beta * 2 * Energy) > random_uniform(rng)) {
						lattice[i][j] *= -1;
						*Energie -= 2 * Energy;
				}
				*Sum_Spins += lattice[i][j];
		}
		return lattice;
}

int main(int argc, char *argv[]) {
		double kbT = 2.27;

		double beta = 1. / kbT;

		int *Energie = new int[n_sweeps];
		int *Sum_Spins = new int[n_sweeps];

		// init random lattice
		int** lattice;
		lattice = init_lattice(m,n);

		// make periodical boundary conditions
		lattice = periodic_lattice(lattice, m, n);
		cout << "Gitter erstellt" << endl;

		ofstream file_init_lattice("./build/02_init.txt");
		if (file_init_lattice.is_open()) {
				for(int x = 0; x < m + 2; ++x){
						for(int y = 0; y < n + 2; ++y){
								file_init_lattice << lattice[x][y] << ",";
						}
						file_init_lattice << endl;
				}
		}

		ofstream file_energy("./build/02_Energie.txt");
		ofstream File_Energy("./build/02_Sum_Spin.txt");
		cout << "Starte " << n_sweeps <<  " Sweeps:" << endl;
		for(int x = 0; x < n_sweeps; ++x){
				if (x % static_cast<int>(n_sweeps / 10.) == 0) {cout << ".";}
				int *p = &Energie[x];
				int *q = &Sum_Spins[x];
				lattice = sweep(lattice, beta, p, q, m, n);
				lattice = periodic_lattice(lattice, m, n);
				file_energy << Energie[x] / (static_cast<double>(n * m)) / 4 << ",";
				File_Energy << Sum_Spins[x]/ (static_cast<double>(n * m)) << ",";
		}
		cout << endl << "Simulation beendet." << endl;


		ofstream file_final_lattice("./build/02_sweep.txt");
		if (file_final_lattice.is_open()) {
				for(int x = 0; x < m + 2; ++x){
						for(int y = 0; y < n + 2; ++y){
								file_final_lattice << lattice[x][y] << ",";
						}
						file_final_lattice << endl;
				}
		}

		// // print lattice
		// cout << "flipped lattice" << endl;
		// for(int x=0; x<m+2 ; ++x){
		// 		for(int y=0; y<n+2 ; ++y){
		// 				cout << lattice[x][y] << ' ';
		// 		}
		// 		cout << endl;
		// }
		return 0;
}
