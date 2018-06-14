import numpy as np
import matplotlib.pyplot as plt


def main():
    ev_all = np.genfromtxt("build/task2b.txt", unpack=True)
    ev_0 = ev_all[: int(len(ev_all) / 2)]
    ev_02 = ev_all[int(len(ev_all) / 2) :]

    ev_0 = sorted(ev_0)
    ev_02 = sorted(ev_02)

    fig, ax = plt.subplots()

    ax.plot(range(len(ev_0)), ev_0, "x-", label=r"$\lambda = $0")
    ax.plot(range(len(ev_02)), ev_02, "x-", label=r"$\lambda = $0.2")

    ax.legend(loc="best")

    ax.set_xlabel(r"# Eigenwert")
    ax.set_ylabel(r"$\lambda$")

    ax.set_xticks(range(len(ev_0)))

    ax.set_title(r"Vergleich der Eigenwerte fuer verschiedene $\lambda$.")

    fig.tight_layout(pad=0)

    fig.savefig("build/plot2b.png", dpi=200)


if __name__ == "__main__":
    main()
