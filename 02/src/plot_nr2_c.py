import numpy as np
import matplotlib.pyplot as plt

exp, uni_exp = np.genfromtxt("build/task2c.txt", delimiter=";", unpack=True)
gauss_rnd_x, gauss_rnd_y = np.genfromtxt("build/task2cI.txt", delimiter=";", unpack=True)


# c)
print("Plotting (2c) ...")

x = np.linspace(-2, 8, 1001)
x_expo = np.linspace(0, 8, 1001)


def gauss(x, mu, sigma_squared):
    return 1 / np.sqrt(2 * np.pi * sigma_squared) * np.exp(
        -(x - mu) ** 2 / (2 * sigma_squared)
    )


def expo(x, mu, k):
    return k * np.exp(-x)


fig = plt.figure()

ax = fig.add_subplot(111)

n_bins = np.linspace(-2, 8, 101)

density = True

frac_points = 1/10000

k = 0.7
mu = 3

# Exp
ax.hist(exp, bins=n_bins, color='C1', density=density, label='exp', alpha=0.4)
ax.scatter(exp[:int(len(exp) * frac_points)], uni_exp[:int(len(exp) * frac_points)], s=10, color='C1', label='Random Numbers')
ax.plot(x_expo+3, expo(x_expo, mu, k), label='exp analytic', color='C1', alpha=0.9)
ax.plot(x_expo-5, expo(x_expo, mu, k)[::-1], label='', color='C1', alpha=0.9)
# Gauss
ax.hist(gauss_rnd_x, bins=n_bins, color='C0', density=density, label='gauss', alpha=0.4)
ax.scatter(gauss_rnd_x[:int(len(gauss_rnd_x) * frac_points)], gauss_rnd_y[:int(len(gauss_rnd_x) * frac_points)], s=10, color='C0', label='Neumann Gauss')
ax.plot(x, gauss(x, mu, 1), label='gauss analytic', color='C0', alpha=0.9)

ax.set_xlim([-2, 8])

ax.legend(loc="best")
ax.set_title("Neumannsches Rueckweisungsverfahren")

fig.tight_layout(pad=0)
fig.savefig("build/plot_02c.png")
plt.close()
