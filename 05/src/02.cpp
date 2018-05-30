// Aufgabe 2: 1D Heisenbergkette
#include <iostream>
#include <Eigen/Dense>

using std::cout;
using std::endl;
using std::pow;

using Eigen::VectorXi;
using Eigen::MatrixXi;
void init_zustaende(int N){
		int dim = (int)pow(2,N);
		MatrixXi mat(dim, N);
		for(int d=0; d<dim; d++){
				for(int n=0; n<N; n++){
						mat(d, N-n-1) = d/(int)pow(2,n)%2;
				}
		}
		cout << "fancy m : " << endl << mat << endl;
}


int main(int argc, char *argv[])
{
		cout << "=============================" << endl;
		cout << "Aufgabe 2: 1D Heisenbergkette" << endl;
		cout << "=============================" << endl << endl;

		init_zustaende(10);

		return 0;
}
