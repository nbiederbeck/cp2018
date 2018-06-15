import numpy as np
import matplotlib.pyplot as plt


def main():
    values = np.genfromtxt("build/task2d.txt", unpack=True)
    values_ = np.genfromtxt("build/task2d_new.txt", unpack=True)
    N = values[::11]

    fig, (ax1, ax2) = plt.subplots(nrows=2)
    for i in [1, 2, 3]:
        ax1.plot(N, values[i::11], "x-", label="{}. Eigenwert".format(i))
        ax2.plot(N, values_[i::11], "x-", label="{}. Eigenwert".format(i))

    ax1.set_xticks(N[::2])

    ax1.set_xlabel(r"$N$")
    ax1.set_ylabel(r"$\lambda$")

    ax1.set_title("Genauigkeit der Eigenwerte in Ortsdarstellung.")
    ax1.legend(loc="best")

    ax2.set_xticks(N[::2])

    ax2.set_xlabel(r"$N$")
    ax2.set_ylabel(r"$\lambda$")

    ax2.set_title("Genauigkeit der Eigenwerte in Besetzungszahldarstellung.")
    ax2.legend(loc="best")

    fig.tight_layout(pad=0.2)
    fig.savefig("build/plot2d.png", dpi=200)


if __name__ == "__main__":
    main()
