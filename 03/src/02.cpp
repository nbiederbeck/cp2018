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
						lattice[x][y] = random_choice(rng);
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
}

int main(int argc, char *argv[])
{
		int m = 5;
		int n = 5;

		// init random lattice
		int** rvalue;
		rvalue = init_lattice(m,n);

		// make periodical boundary conditions
		periodic_lattice(rvalue, m, n);

		// print lattice 
		for(int x=0; x<m+2 ; x++){
				for(int y=0; y<n+2 ; y++){
						cout << rvalue[x][y] << ' ';
				}
				cout << endl;
		}
		return 0;
}
