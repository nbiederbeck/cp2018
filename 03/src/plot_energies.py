import numpy as np
import matplotlib.pyplot as plt

energies = np.genfromtxt("build/02_Energie.txt", delimiter=",")
mags = []
abs_mags = []

n = 100
kbT = 1


fig, ax = plt.subplots()

ax.plot(range(len(energies)), energies, "--", label="Energie")
ax.plot(range(len(mags)), mags, ":", label="Magnetisches Feld")
ax.plot(
    range(len(abs_mags)), abs_mags, "-.", label="Absolutes Magnetisches Feld"
)

ax.set_xlabel("Sweeps")
ax.set_ylabel("e(t), m(t), |m|(t)")
ax.set_xscale("log")
ax.legend()

fig.tight_layout(pad=0)
fig.savefig("build/energies.png")
