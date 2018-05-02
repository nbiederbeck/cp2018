#include <cmath>
#include <random>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
// Aufgabenteil a)
void a() {
		// Initialisierung des Random Number Generators
		// nach Anleitung von Übungsblatt 00
		mt19937 rng;
		rng.seed(random_device()());
		uniform_real_distribution<> dist(0, 1);

		vector<double> randcos;
		for(int i = 0; i<pow(10,5); i++){
				double x = dist(rng);
				randcos.push_back(asin(x));
		}
		
		uniform_real_distribution<> Dist(-1, 1);
		vector<double> Randcos;
		for(int i = 0; i<pow(10,5); i++){
				double x = Dist(rng);
				Randcos.push_back(asin(x));
		}

		ofstream myfile ("./build/task2aI.txt");
		if (myfile.is_open()) {
				for (int i=0; i<randcos.size();i++){
						myfile << randcos[i] << ";" << Randcos[i] << endl;
				}
				myfile.close();
		}
		
}

int main() {
		a();
}

