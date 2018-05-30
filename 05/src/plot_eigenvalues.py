"""Plot all Eigenvalues"""

import numpy as np
import matplotlib.pyplot as plt


class Main:

    def __init__(self):
        pass

    def _make_fig_and_axis(self):
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111)
        self.ax.set_xlabel("# Eigenwert")
        self.ax.set_ylabel(r"$\lambda$")
        self.ax.set_title("Eigenwerte")

    def _plot_eigenvalues(self, ev, label, marker):
        ev_sorted = np.sort(ev)
        xs = range(1, len(ev_sorted) + 1)
        self.ax.scatter(xs, ev_sorted, label=label, marker=marker)
        self.ax.set_xticks(xs)
        self.ax.legend(loc="upper left")

    def main(self):
        # Eigenwerte von Eigen::EigenSolver()
        eigensolver_eigenvalues, _ = np.genfromtxt(
            "build/eigensolver_eigenvalues.txt", unpack=True
        )
        self._make_fig_and_axis()
        self._plot_eigenvalues(eigensolver_eigenvalues, "Eigen::EigenSolver()", "o")

        # Eigenwerte berechnet ueber Diagonalisierung per Hand
        self_solved_eigenvalues, _ = np.genfromtxt(
            "build/hand_eigenvalues.txt", unpack=True
        )
        self._plot_eigenvalues(self_solved_eigenvalues, "Householder-Algorithmus + Jacobi-Rotation", "x")
        self.fig.savefig("build/eigenvalues.png")


if __name__ == "__main__":
    main = Main()
    main.main()
