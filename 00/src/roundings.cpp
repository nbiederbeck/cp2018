#include <iostream>
#include <cmath>

double a1(long i){
		return 1/sqrt(i) - 1/sqrt(i + 1);
}

double a2(long i){
		return 1/sqrt(i*(i + 1))*(sqrt(i + 1)*sqrt(i));
}
int main(){
		for(long i=1; i<pow(10, 12); i=i*10){
			printf("%i %f %f\n", i, a1(i), a2(i));
		}
		return 0;
}
