#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;
long int pseu_rand(int seed, int a, int c, int m){
		return ( a * seed + c ) % m;
}

int rand_pseudo(int seed, int a, int c, long int m, int num) {
		cout << "seed: "<< seed << ", a: " << a 
				<< ", c: " << c << ", m: " << m <<endl;
		vector<float> rand_num{};
		for(int i = 0; i<num; i++) {
				seed = pseu_rand(seed, a, c, m);
				rand_num.push_back(seed /(float) m);
		}
		ofstream myfile ("./build/example.txt");
		if (myfile.is_open()) {
				for (int i=0; i<rand_num.size();i++){
						myfile << rand_num[i] << endl;
				}
				myfile.close();
		}
}

int main() {
		cout << "Aufgabe 1:" << endl;
		long int num = pow(10,1);
		rand_pseudo(1234, 20, 120, 6075, num);
		rand_pseudo(1234, 137, 120, 6075, num);
		rand_pseudo(123456789, 65539, 0, 2147483648, num);
		rand_pseudo(1234, 16807, 0, pow(2,31)-1, num);
}

