#include <iostream>
#include <cmath>
#include <math.h>

void linkongen(int32_t r_0, int32_t a, int32_t c, int32_t m, int32_t n, string file_name){

	ofstream storage;
  	storage.open (file_name.c_str());
  	storage << "Writing this to a file.\n";
  	storage.precision(10);


	int32_t r = r_0;
	for(int32_t i=0; i<n; i++){
		storage << (double) r/m << endl;
		r=(a*r+c)%m;
		if(r<0){cout << "Stop" << endl;}
	}
}


void box_muller(double x_1, double x_2){
	double y_1 = sqrt(-2. * log(x_1))*cos(2. * M_PI * x_2);
	double y_2 = sqrt(-2. * log(x_1))*sin(2. * M_PI * x_2);






}

void box_muller_fast(){
	double v_1 = 2. * rand()-1;
	double v_2 = 2. * rand()-1;

	double r = pow(v_1, 2) + pow(v_2, 2);


}