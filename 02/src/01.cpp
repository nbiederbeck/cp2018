#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;
uint32_t pseu_rand(uint32_t seed, uint32_t a, uint32_t c, uint32_t m){
		return ( a * seed + c ) % m;
}

int rand_pseudo(uint32_t seed, uint32_t a, uint32_t c, 
				uint32_t m, uint32_t num, string file) {
		cout << "seed: "<< seed << ", a: " << a 
				<< ", c: " << c << ", m: " << m <<endl;
		vector<float> rand_num{};
		for(int i = 0; i<num; i++) {
				seed = pseu_rand(seed, a, c, m);
				rand_num.push_back(seed /(float) m);
		}
		ofstream myfile ("./build/" + file);
		if (myfile.is_open()) {
				for (int i=0; i<rand_num.size();i++){
						myfile << rand_num[i] << endl;
				}
				myfile.close();
		}
}

int a() {
		cout << "Aufgabe 1:" << endl;
		long int num = pow(10,5);
		rand_pseudo(1234, 20, 120, 6075, num, "eins.txt");
		rand_pseudo(1234, 137, 120, 6075, num, "zwei.txt");
		rand_pseudo(123456789, 65539, 0, 2147483648, num, "drei.txt");
		rand_pseudo(1234, 16807, 0, pow(2,31)-1, num, "vier.txt");

		cout << "Make fancy Plots:" << endl;
		system("python ./src/plot.py");
}

uint16_t xorshift16(uint16_t seed, uint16_t a, uint16_t b, 
				uint16_t c) {
  seed ^= seed << a;
  seed ^= seed >> b;
  seed ^= seed << c;
  return seed;
}

int rand_xor(uint16_t seed, uint16_t a, uint16_t b, 
				uint16_t c, u_int32_t num, string file) {
		vector<uint16_t> rand_num{};
		for(int i = 0; i<num; i++) {
				seed = xorshift16(seed, a, b, c);
				rand_num.push_back(seed);
		}
		ofstream myfile ("./build/" + file);
		if (myfile.is_open()) {
				for (int i=0; i<rand_num.size();i++){
						myfile << rand_num[i] << endl;
				}
				myfile.close();
		}
}


int main() {
		/* a(); */
		rand_xor(123, 11, 1, 7, pow(10,5), "Eins.txt");
		rand_xor(123, 11, 4, 7, pow(10,5), "Zwei.txt");
		/* int seed = 123; */
		/* for(int i=0; i<100; i++) { */
		/* 		seed = xorshift16(seed, 11, 1, 7); */
		/* 		cout << seed << endl; */
		/* } */
}

