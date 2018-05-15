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

		int **p2DArray;
		p2DArray = new int*[m+2];
		for (int i = 0; i < m+2; ++i)
				p2DArray[i] = new int[n+2];

		// Assign values
		for(int x=1; x<m+1 ; x++){
				for(int y=1; y<n+1 ; y++){
						p2DArray[x][y] = random_choice(rng);
				}
		}

		return p2DArray;
}
int main(int argc, char *argv[])
{
		int m = 2;
		int n=2;
		int** rvalue;
		rvalue = init_lattice(m,n);

		// print lattice 
		for(int x=0; x<m+2 ; x++){
				for(int y=0; y<n+2 ; y++){
						cout << rvalue[x][y] << ' ';
				}
				cout << endl;
		}
		return 0;
}
