#include <cmath>
#include <cstdio>
#include <random>
#include <fstream>
#include <iostream>

/* int lattice(int n, int m){ */
/*     int a[n][m]; */
/* 	return a */
/* } */

using namespace std;
/* int main(int argc, char *argv[]) */
int** init_lattice(int m, int n)
{
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::discrete_distribution<> random_choice({1, 1});


		int **p2DArray;
		p2DArray = new int*[m];
		for (int i = 0; i < m; ++i)
				p2DArray[i] = new int[n];

		// Assign values
		for(int x=0; x<m ; x++){
				for(int y=0; y<n ; y++){
						p2DArray[x][y] = random_choice(rng);
						/* cout<< p2DArray[x][y] << endl; */
				}
		}

		return p2DArray;
}
int main(int argc, char *argv[])
{
		init_lattice(3,4);
		return 0;
}
