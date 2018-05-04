
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <set>

using namespace std;

/* --------------- Methoden fuer Zufallszahlen ----------------------- */
uint32_t pseu_rand(uint32_t seed, uint32_t a, uint32_t c, uint32_t m){
		return ( a * seed + c ) % m;
}

uint16_t xorshift(uint16_t seed, uint16_t a, uint16_t b, 
				uint16_t c) {
  seed ^= seed << a;
  seed ^= seed >> b;
  seed ^= seed << c;
  return seed;
}

/* -------- Zufallszahlen generieren und in file speicheren --------- */
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

int rand_xor(uint16_t seed, uint16_t a, uint16_t b, 
				uint16_t c, u_int32_t num, string file) {
		vector<uint16_t> rand_num{};
		for(int i = 0; i<num; i++) {
				seed = xorshift(seed, a, b, c);
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

int Rand_xor(uint16_t seed, uint16_t a, uint16_t b, 
				uint16_t c, u_int32_t num) {
		set<uint16_t> rand_num{};
		for(int i = 0; i<num; i++) {
				seed = xorshift(seed, a, b, c);
				rand_num.insert(seed);
		}
		return rand_num.size();
}

int b() {
		long int num = pow(10,5);
		rand_pseudo(1234, 20, 120, 6075, num, "eins.txt");
		rand_pseudo(1234, 137, 120, 6075, num, "zwei.txt");
		rand_pseudo(123456789, 65539, 0, 2147483648, num, "drei.txt");
		rand_pseudo(1234, 16807, 0, pow(2,31)-1, num, "vier.txt");
}

int d() {
		rand_xor(123, 11, 1, 7, pow(10,5), "Eins.txt");
		rand_xor(123, 11, 4, 7, pow(10,5), "Zwei.txt");
}

int e() {
		ofstream myfile ("./build/1e.txt");
		if (myfile.is_open()) {
		for(int b=1; b<=15; b++){
				for(int c=1; c<=15; c++){
						int r = Rand_xor(123, 11, b, c, pow(2,16)-1);
						myfile << b << " " << c << " " << r << endl;
				}
		}
				}
				myfile.close();
		}

int main() {
		cout << "Aufgabe 1" << endl;
		cout << "=========" << endl;

		cout << "b)" << endl;
		cout << "--" << endl;
		b();

		cout << "d)" << endl;
		cout << "--" << endl;
		d();

		cout << "e)" << endl;
		cout << "--" << endl;
		e();

		cout << "Aufgabe 1 DONE" << endl;
		cout << "==============" << endl;
}
