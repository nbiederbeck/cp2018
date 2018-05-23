#include <iostream>
#include <random>
#include <Eigen/Dense>
#include <vector>

using namespace Eigen;
int q = 3;
int dim_n = 4;
int dim_m = 4;

std::mt19937 rng;
std::uniform_int_distribution<int> random_n(1,q-1);
std::uniform_int_distribution<int> x_coordi(0,dim_n-1);
std::uniform_int_distribution<int> y_coordi(0,dim_m-1);

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

		int x = x_coordi(rng);
		int y = y_coordi(rng);

		Vector2d pos(x, y);
		std::vector <Vector2d> n_visited = {pos};

		for(int i =0; i<n_visited.size(); i++){
				x = n_visited[i](0);
				y = n_visited[i](1);
				std::cout << x << std::endl;

				// nicht mehr random
				int center = m(x,y);
				int left_h  = m(x,(Y+y-1)%Y);
				int right_h = m(x,(Y+y+1)%Y);
				int above_h = m((X+x-1)%X,y);
				int below_h = m((X+x+1)%X,y);

				int pos[4] = {left_h, right_h, above_h, below_h};


				for(int i=0; i<4; i++){
						if(center == pos[i]){
								std::cout << center << " other pos; " << pos[i] << std::endl;
						}
				}

				/* Vector2d pos(x, y); */
				/* n_visited.push_back(pos); */
				/* std::cout << "---" << std::endl; */
				/* std::cout << n_visited[i] << std::endl; */
		}

		/* for(int i =0; i<sizeof(n_visited); i++){ */
		/* 		std::printf("%d\n", n_visited[i]); */
		/* } */
		// position NN
		/* int center = m(x,y); */
		/* int left_h  = m(x,(Y+y-1)%Y); */
		/* int right_h = m(x,(Y+y+1)%Y); */
		/* int above_h = m((X+x-1)%X,y); */
		/* int below_h = m((X+x+1)%X,y); */

		/* // array for better comp */
		/* int pos[4] = {left_h, right_h, above_h, below_h}; */

		/* int ham = 0; */

		/* for(int i=0; i<4; i++){ */
		/* 		if(center == pos[i]){ */
		/* 				ham += J; */
		/* 		} */
		/* } */
		/* std::printf("%d\n", ham); */
		return m;
}


int main() {
		Eigen::MatrixXd m = init_m(dim_m,dim_m);
		Eigen::MatrixXd H = Hamilton(m, 1.0);
		std::cout << "Here is the matrix m:\n" << H << std::endl;
}
