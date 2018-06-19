#include <iostream>
#include <Eigen/Dense>

using std::cout;
using std::endl;

using namespace Eigen;

int main(int argc, char *argv[])
{
    MatrixXd M(2, 2);
    M << 1, 2,
         3, 4;

    cout << "M = " << endl << M << endl;
    cout << "M * M = " << endl << M * M << endl;
    cout << "M * 3 = " << endl << M * 3 << endl;
    cout << "M.transpose() = " << endl << M.transpose() << endl;

    return 0;
}
