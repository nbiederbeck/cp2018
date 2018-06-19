#include <iostream>
#include <math.h>
#include <random>
#include <Eigen/Dense>
#include <vector>
#include <algorithm>
#include <fstream>
#include <complex>

using namespace Eigen;

int q = 6;
int num = 10000;
int dim_n = 100;
int dim_m = 100;

std::mt19937 rng;
std::uniform_int_distribution<int> random_n(1,q);
std::uniform_int_distribution<int> x_coordi(0,dim_n-1);
std::uniform_int_distribution<int> y_coordi(0,dim_m-1);
std::uniform_real_distribution<> rand_annehmen(0.0, 1.0);

// for magnetic comp calc
double Pi = std::acos(-1);
std::complex<double> li (0,1);


void save_matrix(Eigen::MatrixXd m, const char *filename){
		std::ofstream file (filename, std::ios_base::app);
		file << m << std::endl;
}

void save_array(std::vector <double> array, const char *filename){
		std::ofstream file (filename);
		for(int i=0; i<array.size(); i++){
				file << array[i] << std::endl;
		}
}

std::complex<double> calc_magn(int s){
		double phi = 2*Pi/q*s;
		return std::exp(li * phi);
}

Eigen::MatrixXd init_m(int dim_m, int dim_n, std::complex<double>* magn){
		// Gitter initalisieren und magn messen
		Eigen::MatrixXd m = Eigen::MatrixXd(dim_m, dim_n);
		for(int x=0; x<m.rows(); x++){
				for(int y=0; y<m.cols(); y++){
						m(x,y) = random_n(rng);
						*magn += calc_magn(m(x,y));
				}
		}

		return m;
}


double meas_ener(Eigen::MatrixXd m){
		int X = m.rows();
		int Y = m.cols();
		double energy = 0;
		for(int x=0; x<X; x++){
				for(int y=0; y<Y; y++){
						int center = m(x,y);
						int x_pos[4] = {x, x, (X+x-1)%X, (X+x+1)%X};
						int y_pos[4] = {(Y+y-1)%Y, (Y+y+1)%Y, y, y};
						for(int i=0; i<4; i++){
								if(m(x,y) == m(x_pos[i],y_pos[i])){
										energy += 1;
								}
						}
				}
		}
		return energy;
}


std::vector <Vector2d> Hamilton(Eigen::MatrixXd m , double J){
		int Y = m.cols();
		int X = m.rows();

		int x = x_coordi(rng);
		int y = y_coordi(rng);

		double beta_crit = 1./J*std::log(1. + std::sqrt(q));
		double prop = 1. - std::exp(-2. * beta_crit * J);

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
												n_visited.push_back(new_pos);
										}
								}
						}
				}
				visited.push_back(n_visited[0]);
				n_visited.erase(n_visited.begin(), n_visited.begin()+1);
		}
		return visited;
}


Eigen::MatrixXd swap(Eigen::MatrixXd m, std::vector <Vector2d> cluster, std::complex<double>* pmagn){
		int spin = m(cluster[0](0), cluster[0](1));
		int old_spin = spin;
		while(old_spin == spin){
				spin = random_n(rng);
		}
		for(int i=0; i<cluster.size(); i++){
				m(cluster[i](0), cluster[i](1)) = spin;
		}

		// aenderung der magn 
		std::complex<double> clustersize (cluster.size(), cluster.size());
		*pmagn -= (calc_magn(old_spin) - calc_magn(spin))*clustersize;
		return m;
}

int main(int argc, char *argv[]) {

		std::complex<double> magn (0,0);
		std::complex<double>* pmagn = &magn;

		std::vector <double> srg_magn;
		std::vector <double> srg_energie;

		Eigen::MatrixXd m = init_m(dim_m,dim_m, pmagn);

		for(int i=0; i<num; i++){
				std::cout << i << std::endl;
				std::vector <Vector2d> cluster = Hamilton(m, 1.0);

				m = swap(m, cluster, pmagn);

				srg_magn.push_back(std::norm(magn)/dim_m/dim_n);
				srg_energie.push_back(meas_ener(m)/dim_m/dim_n);

				save_matrix(m, "build/q_6.txt");
		}

		save_array(srg_magn, "build/magn6.txt");
		save_array(srg_energie, "build/energie6.txt");

}
