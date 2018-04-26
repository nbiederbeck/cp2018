#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


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


int main(){
	int64_t N=pow(10,5);
	cout << N << endl;
	linkongen(1234, 20, 120, 6075, N, "a_1_a.txt");


}