import numpy as np
import matplotlib.pyplot as plt

mags = np.genfromtxt("build/02_Sum_Spin.txt", delimiter=",")
abs_mags = np.abs(mags)

kbT = 1


def plot_energies(mags, abs_mags, kbT):
    fig, ax = plt.subplots()
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


fig = plot_energies(mags, abs_mags, kbT)
fig.savefig('build/magn.png')
