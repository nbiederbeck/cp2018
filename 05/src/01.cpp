// Aufgabe 1: Diagonalisierung per Hand
#include <iostream>
#include <Eigen/Dense>

using std::cout;
using std::endl;
using Eigen::MatrixXd;

int main(int argc, char *argv[])
{
    cout << "====================================" << endl;
    cout << "Aufgabe 1: Diagonalisierung per Hand" << endl;
    cout << "====================================" << endl << endl;

	int N = 3;
	MatrixXd m = MatrixXd::Constant(N, N, 1.0);
	MatrixXd d(N,1);
	d << 1, 2, 3;
			/* = MatrixXd::Constant(N, 1, 1.0); */

	m.diagonal() = d;

	/* m = Eigen::MatrixXd::One(N,N); */
    cout << m <<endl ;
    return 0;
}
