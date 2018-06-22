import numpy as np
import matplotlib.pyplot as plt


class plotter:
    def __init__(self, path):
        self.T = np.genfromtxt(path + "T.txt")
        self.r_i = np.genfromtxt(path + "r_i.txt")
        self.v_i = np.genfromtxt(path + "v_i.txt")
        self.r_i_moon = np.genfromtxt(path + "r_i_moon.txt")
        self.v_i_moon = np.genfromtxt(path + "v_i_moon.txt")
        # self.energy = np.genfromtxt(path + "energy.txt")
        # self.momentum = np.genfromtxt(path + "momentum.txt")

    def make_plot(self, path, title, dim, lim=None):
        fig = plt.figure(figsize=(5.78, 3.57))
        ax = fig.add_subplot(111)

        ax.scatter(
            0, 0, label="Sonne", c="C1", marker="o", s=100,
        )

        ax.plot(
            self.r_i[dim, :],
            self.r_i[dim + 1, :],
            label="Planetenbahn",
            c="C0",
        )
        ax.scatter(
            self.r_i[dim, :][0],
            self.r_i[dim + 1, :][0],
            label="Startpunkt",
            marker="x",
            c="C0",
        )

        ax.plot(
            self.r_i_moon[dim, :],
            self.r_i_moon[dim + 1, :],
            label="Mondbahn",
            c="C2",
        )
        ax.scatter(
            self.r_i_moon[dim, :][0],
            self.r_i_moon[dim + 1, :][0],
            marker="x",
            c="C2",
        )

        ax.set_xlabel(r"$x$")
        ax.set_ylabel(r"$y$")
        ax.set_aspect(1)

        ax.set_title(title)
        ax.grid()
        min_x = np.min(
            [
                self.r_i[dim, :],
                self.r_i_moon[dim, :],
            ]
        )
        max_x = np.max(
            [
                self.r_i[dim, :],
                self.r_i_moon[dim, :],
            ]
        )
        ax.set_xlim([1.2 * min_x, 2.2 * max_x])
        if np.allclose(ax.get_ylim(), [0, 0], atol=0.1):
            ax.set_ylim(ax.get_xlim())

        # ax.set_xlim([-4, 4])
        # ax.set_ylim([-4, 4])

        ax.legend(loc="best")

        # ax = fig.add_subplot(122)
        # ax.plot(
        #     np.linspace(0, self.T, len(self.energy)),
        #     self.energy,
        #     label="energy",
        #     c="C0",
        # )
        # ax.plot(
        #     np.linspace(0, self.T, len(self.momentum)),
        #     self.momentum,
        #     label="momentum",
        #     c="C1",
        # )
        # ax.legend()
        # ax.set_xlabel(r"Zeit / $h$")
        # ax.grid()

        fig.tight_layout(pad=0.1)
        fig.savefig(path, dpi=200)

        return lim

    def make_diff(self, path, title, dim, lim=None):
        fig = plt.figure(figsize=(5.78, 3.57))
        ax = fig.add_subplot(111)

        ax.plot(
            # self.r_i[dim, :] - self.r_i_moon[dim, :],
            # self.r_i[dim + 1, :] - self.r_i_moon[dim + 1, :],
            np.linspace(0, self.T, self.r_i_moon.shape[1]),
            np.sum(self.r_i - self.r_i_moon, axis=0) / np.mean(self.r_i - self.r_i_moon),
            label="Mond",
            c="C2",
        )
        ax.plot(
            np.linspace(0, self.T, self.r_i_moon.shape[1]),
            np.zeros(self.r_i_moon.shape[1]),
            label="Planet",
            c="C0",
        )

        ax.set_xlabel(r"Zeit / $h$")
        ax.set_ylabel(r"Relativer Abstand zum Planeten")
        ax.legend(loc="best")
        ax.set_xticks([6 * i for i in range(int(self.T / 4) - 1)])
        ax.grid()
        fig.tight_layout(pad=0.1)
        fig.savefig(path, dpi=200)


def main():
    print("src/plot_2d.py: Plotting (e)")
    p_kepler = plotter("build/kepler_moon/")
    lim = p_kepler.make_plot("build/kepler_moon.png", "Keplerbahnen", 0)
    lim = p_kepler.make_diff("build/moon_planet.png", "Relativbahn", 0)


if __name__ == "__main__":
    main()
    print("src/plot_2d.py: DONE")
