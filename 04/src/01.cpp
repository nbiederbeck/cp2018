#include <iostream>
#include <random>
#include <Eigen/Dense>

using namespace Eigen;
int q = 3;

std::mt19937 rng;
std::uniform_int_distribution<int> random_n(1,q-1);

Eigen::MatrixXd init_m(int dim_m, int dim_n){
		Eigen::MatrixXd m = Eigen::MatrixXd(dim_m, dim_n);
		for(int x=0; x<m.rows(); x++){
				for(int y=0; y<m.cols(); y++){
						m(x,y) = random_n(rng);
				}
		}
		return m;
}


Eigen::MatrixXd Hamilton(Eigen::MatrixXd m , double J){
		int Y = m.cols();
		int X = m.rows();

		for(int y=0; y<Y; y++){
				for(int x=0; x<X; x++){
						// position NN
						int center = m(x,y);
						int left_h  = m(x,(Y+y-1)%Y);
						int right_h = m(x,(Y+y+1)%Y);
						int above_h = m((X+x-1)%X,y);
						int below_h = m((X+x+1)%X,y);

						// array for better comp
						int pos[4] = {left_h, right_h, above_h, below_h};

						int ham = 0;

						for(int i=0; i<4; i++){
								if(center == pos[i]){
										ham += J;
								}
						}
						std::printf("%d\n", ham);
				}
		}
		return m;
}


int main() {
		Eigen::MatrixXd m = init_m(4,4);
		Eigen::MatrixXd H = Hamilton(m, 1.0);
		std::cout << "Here is the matrix m:\n" << H << std::endl;
}
