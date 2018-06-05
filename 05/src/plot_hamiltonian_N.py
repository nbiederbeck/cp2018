import numpy as np
import matplotlib.pyplot as plt

from scipy.optimize import curve_fit


def main():
    fig, ax = plt.subplots()

    N, t = np.genfromtxt("build/hamilton_eigenvalues_N.txt", unpack=True)

    def f(n, x):
        return n ** x

    par, cov = curve_fit(f, N, t)

    xs = np.linspace(np.min(N), np.max(N), 101)

    ax.scatter(N, t, label=r"Laufzeiten", color="C0")
    ax.plot(
        xs,
        f(xs, *par),
        label=r"$t(N) \propto N^x$, $x = " + "{:.2f}".format(par[0]) + "$",
        color="C1",
    )

    # ax.set_yscale("log")
    # ax.set_ylim([1e-6, np.max(t) * 1.2])

    ax.set_xlabel(r"$N$")
    ax.set_ylabel(r"$t \:\:/\:\: 1000 \mu s$")
    ax.legend(loc="best")

    fig.tight_layout(pad=0)
    fig.savefig("build/hamilton_eigenvalues_N.png")


if __name__ == "__main__":
    main()
