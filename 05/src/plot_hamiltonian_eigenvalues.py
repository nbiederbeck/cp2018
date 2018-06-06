import numpy as np
import matplotlib.pyplot as plt


def main():
    fig = plt.figure()
    ax = fig.add_subplot(111)

    ax.set_xlabel("# Eigenwert")
    ax.set_ylabel(r"$\lambda$")
    ax.set_title(r"Eigenwerte Hamiltonmatrix $\mathbf{H}$")

    ev = np.genfromtxt("build/hamiltonian_eigenvalues_final.txt", unpack=True)
    ev_sorted = np.sort(ev)
    xs = range(1, len(ev_sorted) + 1)

    ax.scatter(xs, ev_sorted, label="Eigen::EigenSolver()")
    ax.legend(loc="best")

    fig.tight_layout(pad=0)
    fig.savefig("build/hamiltonian_eigenvalues.png")


if __name__ == "__main__":
    main()
