import numpy as np
import matplotlib.pyplot as plt

fig, ax = plt.subplots()

x = np.linspace(-5, 11, 1001)
data = np.genfromtxt('build/task2b.txt', unpack=True)


def gauss(x, mu, sigma_squared):
    return 1 / np.sqrt(2 * np.pi * sigma_squared) * np.exp(- (x - mu)**2 / (2 * sigma_squared))


ax.plot(x, gauss(x, 3, 4), label='Gauss')
ax.hist(data, bins=100, histtype='step', density=True, label='Box-Muller')
ax.legend(loc='best')

fig.tight_layout(pad=0)
fig.savefig('build/plot_02b.png')
