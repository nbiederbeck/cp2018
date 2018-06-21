import numpy as np
import matplotlib.pyplot as plt


class plotter:
    def __init__(self, path):
        # data = np.genfromtxt(path, delimiter=';')
        self.T = np.genfromtxt(path + "T.txt")
        self.r_i = np.genfromtxt(path + "r_i.txt")
        self.v_i = np.genfromtxt(path + "v_i.txt")
        self.energy = np.genfromtxt(path + "energy.txt")
        self.momentum = np.genfromtxt(path + "momentum.txt")
        # self.r_i = data[1:,0]
        # self.v_i = data[:,1]

    def make_plot(self, path, title, dim, lim=None):
        fig = plt.figure(figsize=(5.78, 3.57))
        ax = fig.add_subplot(121)
        ax.plot(self.r_i[dim, :], self.r_i[dim + 1, :], label="Planetenbahn", c="C0")
        ax.scatter(
            self.r_i[dim, :][0],
            self.r_i[dim + 1, :][0],
            label="Startpunkt",
            marker="x",
            c="C0",
        )
        ax.scatter(0, 0, label="Sonne", c="C1", edgecolor="C0", marker="o", s=100)
        ax.set_xlabel(r"$x$")
        ax.set_ylabel(r"$y$")
        ax.set_aspect(1)

        # ax.legend(loc="best")
        ax.set_title(title)
        ax.grid()

        ax = fig.add_subplot(122)
        ax.plot(
            np.linspace(0, self.T, len(self.energy)),
            self.energy,
            label="energy",
            c="C0",
        )
        ax.plot(
            np.linspace(0, self.T, len(self.momentum)),
            self.momentum,
            label="momentum",
            c="C1",
        )
        ax.legend()
        # ax.set_ylim([, 1.2 * np.max(np.abs(self.energy)) * np.sign(self.energy[0])])
        ax.set_xticks([6 * i for i in range(int(self.T / 4) - 1)])
        ax.set_xlabel(r"Zeit / $h$")
        # ax.set_ylabel("Energie")
        ax.grid()

        fig.tight_layout(pad=0.1)
        fig.savefig(path, dpi=200)

        return lim


def main():
    p_kepler = plotter("build/kepler_euler/")
    lim = p_kepler.make_plot("build/kepler_e.png", "Planetenbahn", 0)
    p_kepler = plotter("build/kepler_rungekutta/")
    lim = p_kepler.make_plot("build/kepler_rk.png", "Planetenbahn", 0)


if __name__ == "__main__":
    main()
