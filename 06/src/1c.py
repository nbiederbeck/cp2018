import numpy as np
import matplotlib.pyplot as plt


def main():
    N, t_lanczos, t_householder, t_eigensolver = np.genfromtxt(
        "build/task1c.txt", unpack=True
    )
    fig, ax = plt.subplots()

    ax.plot(N, t_lanczos, "x-", label="Lanczos + QR")
    ax.plot(N, t_householder, "x-", label="Householder + QR")
    ax.plot(N, t_eigensolver, "x-", label="EigenSolver")

    ax.legend(loc="best")

    ax.set_xlabel(r"$N$")
    ax.set_ylabel(r"$t \:\:/\:\: $s")

    ax.set_xticks(N)

    ax.set_title("Laufzeitvergleich der verschiedenen Verfahren.")

    fig.tight_layout(pad=0)

    fig.savefig("build/plot1c.png", dpi=200)


if __name__ == "__main__":
    main()
