#include <iostream>
#include <math.h>
#include <random>
#include <Eigen/Dense>
#include <vector>
#include <algorithm>

using namespace Eigen;
int q = 4;
int dim_n = 4;
int dim_m = 4;

std::mt19937 rng;
std::uniform_int_distribution<int> random_n(1,q);
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

		double beta_crit = 1./J*std::log(1. + std::sqrt(q));
		double prop = 1. - std::exp(-2. * beta_crit * J);
		std::cout << "critical beta: " << beta_crit << std::endl;
		std::cout << "prop: " << prop << std::endl;

		Vector2d pos(x, y);
		std::vector <Vector2d> n_visited = {pos};
		std::vector <Vector2d> visited = {};

		while(n_visited.empty() != true){
				x = n_visited[0](0);
				y = n_visited[0](1);

				// nicht mehr random
				int center = m(x,y);

				int x_pos[4] = {x, x, (X+x-1)%X, (X+x+1)%X};
				int y_pos[4] = {(Y+y-1)%Y, (Y+y+1)%Y, y, y};

				for(int i=0; i<4; i++){
						if(m(x,y) == m(x_pos[i],y_pos[i])){
								Vector2d new_pos(x_pos[i], y_pos[i]);
								if(std::find(visited.begin(), visited.end(), new_pos) == visited.end()){
										n_visited.push_back(new_pos);
								}
						}
				}

				visited.push_back(n_visited[0]);
				n_visited.erase(n_visited.begin(), n_visited.begin()+1);

				/* 		/1* Vector2d pos(x, y); *1/ */
				/* 		/1* n_visited.push_back(pos); *1/ */
				/* 		/1* std::cout << "---" << std::endl; *1/ */
				/* 		/1* std::cout << n_visited[i] << std::endl; *1/ */
		}

		std::cout << "==========================" << std::endl;
		for(int i=0; i<visited.size(); i++){
				std::cout << "--" << std::endl;
				std::cout << visited[i] << std::endl;
		}
		std::cout << "==========================" << std::endl;

		return m;
}


int main() {
		Eigen::MatrixXd m = init_m(dim_m,dim_m);
		Eigen::MatrixXd H = Hamilton(m, 1.0);
		std::cout << "Here is the matrix m:\n" << H << std::endl;
}
