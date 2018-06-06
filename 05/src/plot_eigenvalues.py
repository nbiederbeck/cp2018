"""Plot all Eigenvalues"""

import numpy as np
import matplotlib.pyplot as plt


class Main:

    def __init__(self):
        pass

    def _make_fig_and_axis(self, title):
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111)
        self.ax.set_xlabel("# Eigenwert")
        self.ax.set_ylabel(r"$\lambda$")
        self.ax.set_title(title)

    def _plot_eigenvalues(self, ev):
        ev_sorted = np.sort(ev)
        xs = range(1, len(ev_sorted) + 1)
        self.ax.scatter(xs, ev_sorted)
        self.ax.set_xticks(xs)

    def main(self):
        # Eigenwerte von Eigen::EigenSolver()
        eigensolver_eigenvalues, _ = np.genfromtxt(
            "build/eigensolver_eigenvalues.txt", unpack=True
        )
        self._make_fig_and_axis("Eigen::EigenSolver()")
        self._plot_eigenvalues(eigensolver_eigenvalues)
        self.fig.savefig("build/eigensolver_eigenvalues.png")

        # Eigenwerte berechnet ueber Diagonalisierung per Hand
        self_solved_eigenvalues, _ = np.genfromtxt(
            "build/eigensolver_eigenvalues.txt", unpack=True
        )
        self._make_fig_and_axis("Eigenwerte per Hand")
        self._plot_eigenvalues(eigensolver_eigenvalues)
        self.fig.savefig("build/hand_eigenvalues.png")


if __name__ == "__main__":
    main = Main()
    main.main()
