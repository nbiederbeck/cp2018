import numpy as np
import matplotlib.pyplot as plt


def plot_hamiltonian():
    H = np.genfromtxt("build/hamiltonian.txt", unpack=True)

    absmax = np.max(np.abs([np.min(H), np.max(H)]))

    fig, ax = plt.subplots()

    grid = np.meshgrid(range(len(H)), range(len(H)))
    cmap = plt.get_cmap("RdBu", 2 * absmax)
    hamiltonian = ax.pcolormesh(*grid, H, cmap=cmap, vmin=-absmax, vmax=absmax)

    ax.set_xlabel(r"# des Eingangsvektors $\vec{e}$")
    ax.set_ylabel(r"# des Ausgangsvektors $\vec{a}$")
    ax.set_title(r"Hamiltonmatrix $\mathbf{H}$")

    cbar = fig.colorbar(hamiltonian)
    cbar.ax.set_ylabel(r"Wert des Eintrages")

    ax.set_aspect(1)
    fig.tight_layout(pad=0)
    fig.savefig("build/hamiltonian.png")


if __name__ == "__main__":
    plot_hamiltonian()
