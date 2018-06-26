import numpy as np
import matplotlib.pyplot as plt


def main():
    ev_all = np.genfromtxt("build/task1b.txt", unpack=True)
    ev_qr = ev_all[: int(len(ev_all) / 2)]
    ev_es = ev_all[int(len(ev_all) / 2):]

    ev_qr = sorted(ev_qr)
    ev_es = sorted(ev_es)

    fig, ax = plt.subplots()

    ax.plot(range(len(ev_qr)), ev_qr, "x-", label="QR-Iteration")
    ax.plot(range(len(ev_es)), ev_es, "x-", label="EigenSolver")

    ax.legend(loc="best")

    ax.set_xlabel(r"# Eigenwert")
    ax.set_ylabel(r"$\lambda$")

    ax.set_title("Vergleich der Eigenwerte.")

    fig.tight_layout(pad=0)

    fig.savefig("build/plot1b.png", dpi=200)


if __name__ == "__main__":
    main()
