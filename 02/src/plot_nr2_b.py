import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots()

x = np.linspace(-5, 11, 1001)
X, Y = np.genfromtxt("build/task2b.txt", delimiter=";", unpack=True)
X = np.append(X, Y)


def gauss(x, mu, sigma_squared):
    return 1 / np.sqrt(2 * np.pi * sigma_squared) * np.exp(
        -(x - mu) ** 2 / (2 * sigma_squared)
    )


print("Plotting (2b) ...")
ax.plot(x, gauss(x, 3, 4), label="Gauss")
ax.hist(X, bins=100, histtype="step", density=True, label="Box-Muller")
ax.legend(loc="best")

fig.tight_layout(pad=0)
fig.savefig("build/plot_02b.png")
