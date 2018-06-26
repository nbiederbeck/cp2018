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
        fig = plt.figure()
        ax = fig.add_subplot(211)
        ax.plot(
            np.linspace(0, self.T, len(self.r_i[dim, :])),
            self.r_i[dim, :],
            label="r(t)",
        )
        ax.plot(
            np.linspace(0, self.T, len(self.v_i[dim, :])),
            self.v_i[dim, :],
            label="v(t)",
        )
        ax.set_xlabel("time")
        ax.set_ylabel("Amplitude")

        # ax.set_xlim([0, 2 * np.pi])
        # ax.set_ylim([-1.5, 1.5])
        if lim is None:
            lim = 1.2 * np.max(np.abs([self.v_i, self.r_i]))
        ax.set_ylim([-lim, lim])

        ax.legend(loc="best")
        ax.set_title(title)
        ax.grid()

        ax = fig.add_subplot(212)
        ax.plot(np.linspace(0, self.T, len(self.energy)), self.energy, label="Energie")
        ax.legend()
        ax.set_ylim([0, 1.2 * np.max(self.energy)])

        fig.tight_layout(pad=0.1)
        fig.savefig(path)

        return lim

def main():
    print("src/plot_1.py: Plotting (a)")
    p_euler = plotter("build/euler/")
    lim = p_euler.make_plot("build/euler.png", "Euler Verfahren", 0)
    p_runge = plotter("build/runge2/")
    p_runge.make_plot("build/runge2.png", "Runge Verfahren 2. Ordnung", 0, lim)
    p_runge = plotter("build/runge4/")
    p_runge.make_plot("build/runge4.png", "Runge Verfahren 4. Ordnung", 0, lim)

    print("src/plot_1.py: Plotting (b)")
    p_runge = plotter("build/b1/")
    p_runge.make_plot("build/b1.png", "r(0) beliebig, v(0) = 0", 0)
    p_runge = plotter("build/b2/")
    p_runge.make_plot("build/b2.png", "r(0) beliebig, v(0) beliebig", 0)
    p_runge = plotter("build/b3/")
    p_runge.make_plot("build/b3.png", "r(0) senkrecht v(0)", 0)


if __name__ == "__main__":
    main()
    print("src/plot_1.py: DONE")
