// vim: commentstring=//%s autoindent tabstop=4 shiftwidth=4 softtabstop=4 expandtab
// Aufgabe 2: 1D Heisenbergkette
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
#include <ctime>

using std::cout;
using std::endl;
using std::pow;
using std::vector;
using std::clock;

using Eigen::VectorXi;
using Eigen::MatrixXi;

using Eigen::EigenSolver;
using Eigen::MatrixXd;
using Eigen::MatrixXcd;

MatrixXi init_zustaende(int); // Erstelle Alle Spins in Binaerschreibweise
MatrixXi spin_sum(MatrixXi m , int spin); // Berechne Spinsumme der Zustaende
int zustandssumme(VectorXi);
VectorXi permutation(VectorXi, int);
MatrixXd hamilton_matrix_from_spins(MatrixXi, double J = 1.0);
int spin_encoder(MatrixXi, int);
void test();
void save_matrices_to_file(MatrixXd, const char *filename);
void run_b(int);
void run_c();

int main() {
    cout << "=============================" << endl;
    cout << "Aufgabe 2: 1D Heisenbergkette" << endl;
    cout << "=============================" << endl << endl;

    int N = 10;
    run_b(N);
    run_c();

    return 0;
}

void run_b(int N) {
    MatrixXi spins;
    spins = init_zustaende(N);
    spins = spin_sum(spins, 0);

    MatrixXd H;
    H = hamilton_matrix_from_spins(spins);

    save_matrices_to_file(H, "build/hamiltonian.txt");

    EigenSolver<MatrixXd> es(H.cast<double>());

    MatrixXcd ev = es.eigenvalues();
    std::ofstream file ("build/hamiltonian_eigenvalues.txt");
    file << ev << endl;
}

void run_c() {
    std::ofstream file ("build/hamilton_eigenvalues_N.txt");

    cout << "Code being run per iteration and time measurement: " << endl;
    cout << "EigenSolver<MatrixXd> es(H.cast<double>());" << endl;
    cout << "es.eigenvalues();" << endl;

    for (int N = 2; N <= 14; N+=2) {
        MatrixXi spins;
        spins = init_zustaende(N);
        spins = spin_sum(spins, 0);

        MatrixXd H;
        H = hamilton_matrix_from_spins(spins);

        clock_t begin = clock();
        EigenSolver<MatrixXd> es(H.cast<double>());
        es.eigenvalues();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        cout << "N=" << N << ", t=" << elapsed_secs << "s" << endl;
        file << N << " " << elapsed_secs << endl;
    }
}

// Eine Testfunktion
void test() {
    int N = 4;
    VectorXi v(N);
    VectorXi v_perm(N);
    int s;

    v << 1, 0, 1, 0;
    cout << "Vektor:" << endl << v << endl;

    s = zustandssumme(v);
    cout << "Spinzustandsdarstellung: |" << s << ">" << endl;

    int i = 0;
    for (i = 0; i<N; i++) {
        v_perm = permutation(v, i);
        cout << "Vektor nach Permutation " << i << ", " << i+1 << ": " << endl << v_perm << endl;
        s = zustandssumme(v_perm);
        cout << "Spinzustandsdarstellung: |" << s << ">" << endl;
    }
}

// Erstelle Alle Spins in Binaerschreibweise
MatrixXi init_zustaende(int N) {
    int dim = (int)pow(2,N);
    MatrixXi mat(dim, N);
    for(int d = 0; d < dim; d++) {
        for(int n = 0; n < N; n++) {
            mat(d, N - n - 1) = d / (int)pow(2, n) % 2;
        }
    }
    return mat;
}

// Berechne Spinsumme der Zustaende
MatrixXi spin_sum(MatrixXi m , int spin) {
    // Spins have value 0 or 1 and not +-1/2
    double bias = m.cols() / 2;
    VectorXi m_spin = m.rowwise().sum().array() - (int)bias;

    vector<int> z;
    for(int i = 0; i < m_spin.rows(); i++) {
        if(m_spin(i) == spin){
            z.push_back(i);
        }
    }
    MatrixXi spinsums(z.size(), m.cols());
    for(int i = 0; i < z.size(); i++) {
        spinsums.row(i) = m.row(z[i]);
    }

    return spinsums;
}

// Berechne die Hamiltonmatrix aus gegebenen Spins
MatrixXd hamilton_matrix_from_spins(MatrixXi spins, double J) {
    int dim = spins.rows();
    MatrixXd H(dim, dim) ;
    H = MatrixXd::Zero(dim, dim);

    int y;

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < spins.cols(); j++) {
            y = spin_encoder(spins, zustandssumme(permutation(spins.row(i), j)));
            H(i, y) += J / 4.0 * 2.0;  // Permutationsteil von $H = J/4 sum( 2P - 1 )$
            H(i, i) -= J / 4.0 * 1.0;  // -1 Teil vom Hamiltonian
        }
    }

    return H;
}

int spin_encoder(MatrixXi spinvec, int need_spin) {
    int dim = spinvec.rows();
    VectorXi spinzustaende(dim);

    for (int i = 0; i < dim; i++) {
        spinzustaende(i) = zustandssumme(spinvec.row(i));
    }

    for (int i = 0; i < dim; i++) {
        if (spinzustaende(i) == need_spin) {
            return i;
        }
    }
    return 666;
}

// Berechne Binardaerstellung des Spins (eindeutige Darstellung)
int zustandssumme(VectorXi vec) {
    int zustandssumme = 0;
    for (int i = 0; i < vec.rows(); i++) {
        zustandssumme += vec(i) * pow(2, vec.rows() - i - 1);
    }
    return zustandssumme;
}

// Permutiere Eintrag  i mit Eintrag i+1 eines Vektors
VectorXi permutation(VectorXi vec, int i) {
    int N = vec.rows();
    int j = (N + i + 1 ) % N;
    int temp = vec(i);
    vec(i) = vec(j);
    vec(j) = temp;
    return vec;
}

// Save Matrix to Filename
void save_matrices_to_file(MatrixXd mat, const char *filename) {
    std::ofstream file (filename);
    file << mat << endl;
}
