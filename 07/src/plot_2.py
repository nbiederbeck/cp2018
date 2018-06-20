import numpy as np
import matplotlib.pyplot as plt


class plotter:
    def __init__(self, path):
        # data = np.genfromtxt(path, delimiter=';')
        self.T = np.genfromtxt(path + "T.txt")
        self.r_i = np.genfromtxt(path + "r_i.txt")
        self.v_i = np.genfromtxt(path + "v_i.txt")
        self.energy = np.genfromtxt(path + "energy.txt")
        # self.r_i = data[1:,0]
        # self.v_i = data[:,1]

    def make_plot(self, path, title, dim, lim=None):
        fig = plt.figure(figsize=(5.78, 3.57))
        ax = fig.add_subplot(121)
        ax.plot(
            self.r_i[dim, :],
            self.r_i[dim+1, :],
            label="Planetenbahn",
            c="C0"
        )
        ax.scatter(
            self.r_i[dim, :][0],
            self.r_i[dim+1, :][0],
            label="Startpunkt",
            marker="x",
            c="C0"
        )
        ax.scatter(0,0,label="Sonne", c="C1", edgecolor="C0", marker="o", s=100)
        ax.set_xlabel(r"$x$")
        ax.set_ylabel(r"$y$")
        ax.set_aspect(1)

        # ax.legend(loc="best")
        ax.set_title(title)
        ax.grid()

        ax = fig.add_subplot(122)
        ax.plot(np.linspace(0, self.T, len(self.energy)), self.energy, label="Energie", c="C0")
        ax.legend()
        ax.set_ylim([0, 1.2 * np.max(self.energy)])
        ax.set_xticks([6*i for i in range(5)])
        ax.set_xlabel(r"Zeit / $h$")
        ax.set_ylabel("Energie")
        ax.grid(axis="x")

        fig.tight_layout(pad=0.1)
        fig.savefig(path)

        return lim

def main():
    p_kepler = plotter("build/kepler/")
    lim = p_kepler.make_plot("build/kepler.png", "Planetenbahn", 0)


if __name__ == "__main__":
    main()
