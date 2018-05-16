#include <cmath>
#include <cstdio>
#include <random>
#include <fstream>
#include <iostream>

using namespace std;
int** init_lattice(int m, int n)
{
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::discrete_distribution<> random_choice({1, 1});

		// init n+2xm+2 array
		int **lattice;
		lattice = new int*[m+2];
		for (int i = 0; i < m+2; ++i)
				lattice[i] = new int[n+2];

		// Assign values
		for(int x=1; x<m+1 ; x++){
				for(int y=1; y<n+1 ; y++){
						if(random_choice(rng)==0){
								lattice[x][y] = -1;
						}
						else{
								lattice[x][y] = 1;
						}
				}
		}
		return lattice;
}

int** periodic_lattice(int** lattice, int m, int n){
		for(int i=1; i<m+1; i++){
				lattice[0][i] = lattice[m][i];
				lattice[m+1][i] = lattice[1][i];
		}
		for(int i=1; i<n+1; i++){
				lattice[i][0] = lattice[i][n];
				lattice[i][n+1] = lattice[i][1];
		}
		return lattice;
}

int** sweep(int** old_lattice, int** new_lattice, double beta, int m, int n){
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_real_distribution<double> random_uniform(0, 1);

		for(int i=1; i<m+1; i++){
				for(int j=1; j<n+1; j++){
						int Energy = -old_lattice[i][j] * (old_lattice[i][j-1] + old_lattice[i][j+1] + old_lattice[i-1][j] + old_lattice[i+1][j]);
						/* cout << Energy << endl; */
						if(-2 * Energy < 0){
								/* cout << i << j << "alter eintrag" << old_lattice[i][j] << "new lattice" << new_lattice[i][j] << endl; */
								new_lattice[i][j] = -1 * old_lattice[i][j];
						}
						else{ 
								if(exp(beta * 2 * Energy) > random_uniform(rng)){
										new_lattice[i][j] = -1 * old_lattice[i][j];
								}
								else{
										new_lattice[i][j] = old_lattice[i][j];
								}
						}
				}
		}
		return new_lattice;
}

int main(int argc, char *argv[])
{
		int m = 5;
		int n = 5;
		double beta = 100;

		// init random lattice
		int** old_lattice;
		old_lattice = init_lattice(m,n);
		int** new_lattice;
		new_lattice = init_lattice(m,n);

		// make periodical boundary conditions
		old_lattice = periodic_lattice(old_lattice, m, n);
		cout << "Gitter erstellt" << endl;

		/* // print lattice */ 
		/* for(int x=0; x<m+2 ; x++){ */
		/* 		for(int y=0; y<n+2 ; y++){ */
		/* 				cout << old_lattice[x][y] << ' '; */
		/* 		} */
		/* 		cout << endl; */
		/* } */

		std::ofstream myfile("./build/02_init.txt");
		if (myfile.is_open()) {
				for(int x=0; x<m+2 ; x++){
						for(int y=0; y<n+2 ; y++){
								myfile << old_lattice[x][y] << ",";
						}
						myfile << endl;
				}

		}

		old_lattice = sweep(old_lattice, new_lattice, beta, m, n);
		
		std::ofstream Myfile("./build/02_sweep.txt");
		if (myfile.is_open()) {
				for(int x=0; x<m+2 ; x++){
						for(int y=0; y<n+2 ; y++){
								Myfile << old_lattice[x][y] << ",";
						}
						Myfile << endl;
				}

		}

		// print lattice 
		cout << "flipped lattice" << endl;
		for(int x=0; x<m+2 ; x++){
				for(int y=0; y<n+2 ; y++){
						cout << old_lattice[x][y] << ' ';
				}
				cout << endl;
		}
		return 0;
}
