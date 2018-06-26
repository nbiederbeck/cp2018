#include <iostream>
#include <iomanip>
#include <complex>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <sstream>
#include <utility>
#include <math.h>
#include <fstream>
#include <functional>
using namespace std;

double mu = 1/2;
double g = 9.81;
double lambda = 1;
double m_1 = 1;
double m_2 = 1;
double L = 1;




double E_pot(double theta_1, double theta_2){
	
	double E_pot = -(m_1 + m_2)*g*L*cos(theta_1) -m_2*g*L*cos(theta_2);

	return E_pot;

}

double E_kin(double theta_del_1, double theta_del_2){

	double E_kin = 1/2 * m_1 * std::pow	(L, 2) * std::pow(theta_del_1, 2) + 1/2 * m_2* (std::pow(L, 2)*std::pow(theta_del_1, 2) + std::pow(L, 2)*std::pow(theta_del_2, 2) + 2*L*L*theta_del_1*theta_del_2*cos(theta_1 - theta_2) )

	return E_kin;
}


double runge_kutta_4o(){

	/* Init for theta_1 and theta_2 theta_del_1 theta_del_2 */
	vector<double> k_1(4);
	vector<double> k_2(4);
	vector<double> k_3(4);
	vector<double> k_4(4);





}