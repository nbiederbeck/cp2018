#include <iostream>
#include <cmath>

float a1(float i){
    return 1/sqrt(i) - 1/sqrt(i + 1);
}

float a2(float i){
    return 1/(sqrt(i*(i + 1))*(sqrt(i + 1)*sqrt(i)));
}

float b1(float i) {
    return (1 - cos(i)) / sin(i);
}

float b2(float i) {
    return tan(i / 2);
}

void a() {
    printf("Task 2: \n");
    printf("a) \n");
    float rel_err = pow(10, -6);
    float a_1, a_2;
    for(float i = pow(10, 2); i < pow(10, 7); i++){
        a_1 = a1(i);
        a_2 = a2(i);
        printf("%f %f\n", a_1, a_2);
        if (pow(a_1 - a_2, 2)/a_2 < rel_err) {
            printf("%f\n", float(i));
            break;
        }
    }
}

void b() {
    printf("Task 2: \n");
    printf("b) \n");
    float rel_err = pow(10, -6);
    float b_1, b_2;
    for(float i = pow(10, -2); i > pow(10, -7); i = i/10){
        b_1 = b1(i);
        b_2 = b2(i);
        printf("%f %f\n", b_1, b_2);
        if (pow(b_1 - b_2, 2) < rel_err) {
            printf("%f\n", float(i));
            break;
        }
    }
}

int main(){
    a();
    b();
    // c();
    return 0;
}
