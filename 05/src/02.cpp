// vim: commentstring=//%s
// Aufgabe 2: 1D Heisenbergkette
#include <iostream>
#include <Eigen/Dense>

using std::cout;
using std::endl;

using Eigen::VectorXi;

int spinzustand(VectorXi);
VectorXi permutation(VectorXi, int, int);

void test();

int main()
{
    cout << "=============================" << endl;
    cout << "Aufgabe 2: 1D Heisenbergkette" << endl;
    cout << "=============================" << endl << endl;

    test();

    return 0;
}

int spinzustand(VectorXi vec) {
    int sum = 0;
    for (int i = 0; i < vec.rows(); i++) {
        sum += vec(i) * pow(2, vec.rows() - i - 1);
    }
    return sum;
}

VectorXi permutation(VectorXi vec, int i, int j) {
    int temp = vec(i);
    vec(i) = vec(j);
    vec(j) = temp;
    return vec;
}

void test() {
    VectorXi v(4);
    int s;

    v << 1, 0, 1, 0;
    cout << "Vektor:" << endl << v << endl;

    s = spinzustand(v);
    cout << "Spinzustandsdarstellung: |" << s << ">" << endl;

    int i, j;
    i = 0;
    j = 3;
    v = permutation(v, i, j);
    cout << "Vektor nach Permutation " << i << ", " << j << ": " << endl << v << endl;

    s = spinzustand(v);
    cout << "Spinzustandsdarstellung: |" << s << ">" << endl;
}
