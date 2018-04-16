#include <iostream>
#include <cmath>

double a1(double i){
		return 1/sqrt(i) - 1/sqrt(i + 1);
}

double a2(double i){
		return 1/(sqrt(i*(i + 1))*(sqrt(i + 1)*sqrt(i)));
}

int main(){
		printf("Task 1: \n");
		printf("a) \n");
		for(long long int i = 1; i<pow(10, 12); i=i*10){
			printf("%lld %f %f\n", i, a1(i), a2(i));
		}
		return 0;
}
