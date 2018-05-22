import numpy as np
import matplotlib.pyplot as plt

from scipy.optimize import curve_fit

N, mean_r = np.genfromtxt('build/data.txt', unpack=True)

def f(x, m, b, i):
    return m*x**i + b

par, cov = curve_fit(f, N, mean_r)
x = np.linspace(np.min(N), np.max(N), 101)

fig, ax = plt.subplots()
ax.plot(N, mean_r, 'x--')
ax.plot(x, f(x, *par), '-', label='r = {}N^({}) + {}'.format(*np.round(par, 3)))

ax.set_xlabel('N')
ax.set_ylabel('r')
ax.legend(loc='best')
fig.tight_layout(pad=0)
fig.savefig('build/plot_01.pdf')
