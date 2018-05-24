#include <iostream>
#include <math.h>
#include <random>
#include <Eigen/Dense>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace Eigen;

int q = 3;
int dim_n = 100;
int dim_m = 100;

std::mt19937 rng;
std::uniform_int_distribution<int> random_n(1,q);
std::uniform_int_distribution<int> x_coordi(0,dim_n-1);
std::uniform_int_distribution<int> y_coordi(0,dim_m-1);
std::uniform_real_distribution<> rand_annehmen(0.0, 1.0);

Eigen::MatrixXd init_m(int dim_m, int dim_n){
		Eigen::MatrixXd m = Eigen::MatrixXd(dim_m, dim_n);
		for(int x=0; x<m.rows(); x++){
				for(int y=0; y<m.cols(); y++){
						m(x,y) = random_n(rng);
				}
		}
		return m;
}

std::vector <Vector2d> Hamilton(Eigen::MatrixXd m , double J){
		int Y = m.cols();
		int X = m.rows();

		int x = x_coordi(rng);
		int y = y_coordi(rng);

		double beta_crit = 1./J*std::log(1. + std::sqrt(q));
		double prop = 1. - std::exp(-2. * beta_crit * J);
		/* std::cout << "critical beta: " << beta_crit << std::endl; */
		/* std::cout << "prop: " << prop << std::endl; */

		Vector2d pos(x, y);
		std::vector <Vector2d> n_visited = {pos};
		std::vector <Vector2d> visited = {};

		while(n_visited.empty() != true){
				x = n_visited[0](0);
				y = n_visited[0](1);

				int center = m(x,y);
				int x_pos[4] = {x, x, (X+x-1)%X, (X+x+1)%X};
				int y_pos[4] = {(Y+y-1)%Y, (Y+y+1)%Y, y, y};

				for(int i=0; i<4; i++){
						if(m(x,y) == m(x_pos[i],y_pos[i])){
								Vector2d new_pos(x_pos[i], y_pos[i]);
								if(std::find(visited.begin(), visited.end(), new_pos) == visited.end() &&
												std::find(n_visited.begin(), n_visited.end(), new_pos) == n_visited.end()
								  ){
										if(rand_annehmen(rng) < prop){
												/* std::cout << "Angenommen" << std::endl; */
												n_visited.push_back(new_pos);
										}
										else{
												/* std::cout << "Abgelehnt" << std::endl; */
										}
								}
						}
				}
				visited.push_back(n_visited[0]);
				n_visited.erase(n_visited.begin(), n_visited.begin()+1);
		}
		return visited;
}


Eigen::MatrixXd swap(Eigen::MatrixXd m, std::vector <Vector2d> cluster){
		int spin = m(cluster[0](0), cluster[0](1));
		/* std::cout << "pos: (" << cluster[0](0) << "," << cluster[0](1) << ") has spin: " << spin << std::endl; */
		int old_spin = spin;
		while(old_spin == spin){
				spin = random_n(rng);
		}
		/* std::cout << "new spin: " << spin << std::endl; */
		for(int i=0; i<cluster.size(); i++){
				m(cluster[i](0), cluster[i](1)) = spin;
		}
		return m;
}

void save_matrix(Eigen::MatrixXd m, const char *filename){
		std::ofstream file (filename, std::ios_base::app);
		file << m << std::endl;
}

int main() {
		Eigen::MatrixXd m = init_m(dim_m,dim_m);
		for(int i=0; i<1000; i++){
				std::cout << i << std::endl;
		std::vector <Vector2d> cluster = Hamilton(m, 1.0);
		/* std::cout << "the old matrix m:\n" << m << std::endl; */
		/* std::cout << "==========================" << std::endl; */

		m = swap(m, cluster);
		/* std::cout << "==========================" << std::endl; */
		/* std::cout << "the new matrix m:\n" << m << std::endl; */
		save_matrix(m, "build/test.txt");
		}
}
