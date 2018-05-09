import numpy as np
import matplotlib.pyplot as plt


def plot_01_b():
    H, p1, p2, _ = np.genfromtxt("build/01_b.txt", delimiter=",", unpack=True)
    p1 *= 1  # Spin = 1
    p2 *= 1  # Spin = -1

    fig, ax = plt.subplots()
    fig.set_size_inches(5.73, 3.57)

    ax.scatter(H, p1, label=r'$s = 1$')
    ax.scatter(H, p2, label=r'$s = -1$')

    ax.set_xlabel(r'$H$')
    ax.set_ylabel(r'$p(m(H))$')
    ax.legend(loc='best')

    fig.tight_layout(pad=0)
    fig.savefig("build/plot_01_b.png")


if __name__ == "__main__":
    plot_01_b()
