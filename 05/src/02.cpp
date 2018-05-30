// vim: commentstring=//%s
// Aufgabe 2: 1D Heisenbergkette
#include <iostream>
#include <vector>
#include <Eigen/Dense>

using std::cout;
using std::endl;
using std::pow;
using std::vector;

using Eigen::VectorXi;
using Eigen::MatrixXi;

int spinzustand(VectorXi);
VectorXi permutation(VectorXi, int);

MatrixXi init_zustaende(int N){
		int dim = (int)pow(2,N);
		MatrixXi mat(dim, N);
		for(int d=0; d<dim; d++){
				for(int n=0; n<N; n++){
						mat(d, N-n-1) = d/(int)pow(2,n)%2;
				}
		}
		return mat;
}

MatrixXi spin_sum(MatrixXi m , int spin){
		// matrix with spins with corresponding spin
		// bias because spin 0 is value 0 and not 0.5
		double bias = m.cols()/2;
		cout << "Bias: " << bias << " have to be checked! " << endl;

		VectorXi m_spin = m.rowwise().sum().array()-(int)bias;
		vector<int> z;
		for(int i=0; i<m_spin.rows(); i++){
				if(m_spin(i) == spin){
						z.push_back(i);
				}
		}
		MatrixXi spins(z.size(), m.cols());
		for(int i=0; i<z.size(); i++){
						spins.row(i) = m.row(z[i]);
		}

		return spins;
}

void test();

int main()
{
		cout << "=============================" << endl;
		cout << "Aufgabe 2: 1D Heisenbergkette" << endl;
		cout << "=============================" << endl << endl;

		int N = 4;
		MatrixXi spins;
		spins = init_zustaende(N);
		spins = spin_sum(spins, 0);
		for(int i = 0; i<spins.rows(); i++ ){
				cout << " |" << spinzustand(spins.row(i)) << ">" << endl;
		}

		double E = 0;
		for (int i = 0; i < N; i++) {
				E += 2 * spinzustand(permutation(spins.row(0), i));
		}
		E -= (double)N * spinzustand(spins.row(0));
		std::cout << E << std::endl;
		
		// test();

		return 0;
}

MatrixXi hamilton_matrix_from_spins(MatrixXi spins) {
		int dim = spins.rows();
		// MatrixXi H(dim, dim) ;
		H = MatrixXi::Zero(dim, dim);

		// An welcher Stelle in der Hamiltonmatrix steht der permutierte Vektor
		// (spin_encoder) ?
		// An dieser Stelle die Hamiltonmatrix um den entsprechenden Faktor erhoehen
		// Dafuer jede Permutation von jedem Spinvektor berechnen, um die
		// entsprechenden Faktoren zu erhalten.

		// for (int i = 0; i < dim; i++) {
		// 		for (int j = 0; j < spins.cols(); j++) {
		// 				H(x, y) += spin_encoder(permutation(spins.row(i), j));
		// 		}
		// }
}

int spinzustand(VectorXi vec) {
		int sum = 0;
		for (int i = 0; i < vec.rows(); i++) {
				sum += vec(i) * pow(2, vec.rows() - i - 1);
		}
		return sum;
}

VectorXi permutation(VectorXi vec, int i) {
		int N = vec.rows();
		int j = (N + i + 1 ) % N;
		int temp = vec(i);
		vec(i) = vec(j);
		vec(j) = temp;
		return vec;
}

void test() {
		VectorXi v(4);
		int s;

		v << 1, 0, 1, 0;
		cout << "Vektor:" << endl << v << endl;

		s = spinzustand(v);
		cout << "Spinzustandsdarstellung: |" << s << ">" << endl;

		int i = 3;
		v = permutation(v, i);
		cout << "Vektor nach Permutation " << i << ", " << i+1 << ": " << endl << v << endl;

		s = spinzustand(v);
		cout << "Spinzustandsdarstellung: |" << s << ">" << endl;
}
