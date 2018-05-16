import numpy as np
import matplotlib.pyplot as plt

energies = np.genfromtxt("build/02_Energie.txt", delimiter=",")
mags = []
abs_mags = []

n = 100
kbT = 1


def plot_energies(energies, mags, abs_mags, kbT, n):
    fig, ax = plt.subplots()
    ax.plot(range(len(energies)), energies, "C1-", label="Energy")
    ax.plot(range(len(mags)), mags, "C3--", label="Magnetic Field")
    ax.plot(
        range(len(abs_mags)), abs_mags, "C2:", label="Absolute Magnetic Field"
    )
    ax.set_xlabel("Sweeps")
    ax.set_ylabel("e(t)")
    ax.set_xscale('log')
    ax.legend()
    fig.tight_layout(pad=0)
    return fig


fig = plot_energies(energies, mags, abs_mags, kbT, n)
fig.savefig('build/energies.png')
