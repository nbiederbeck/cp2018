import numpy as np
import matplotlib.pyplot as plt

marker_size = 20


def plot_01_b():
    print('read data')
    H, p1, p2, _ = np.genfromtxt("build/01_b.txt", delimiter=",", unpack=True)
    p1 *= 1  # Spin = 1
    p2 *= 1  # Spin = -1

    fig, ax = plt.subplots()
    fig.set_size_inches(5.73, 3.57)

    print('scatter data')
    ax.scatter(H, p1, c='C1', s=marker_size, alpha=0.5)
    # ax.scatter(H, p2, label=r'$s = -1$', s=marker_size)

    x = np.linspace(-5, 5, 1001)
    # ax.plot(x, -np.tanh(x), c='C1', label=r'$-\tanh(H)$')
    ax.plot(-x, np.tanh(-x), c='C0', label=r'$+\tanh(H)$')

    ax.set_xlabel(r'$H$')
    ax.set_ylabel(r'$p(m(H))$')
    ax.legend(loc='best')

    fig.tight_layout(pad=0)
    fig.savefig("build/plot_01_b.png")
    print('plot saved')


if __name__ == "__main__":
    plot_01_b()
