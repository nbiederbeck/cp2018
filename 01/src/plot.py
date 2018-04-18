import numpy as np
import matplotlib.pyplot as plt

N, mean_r = np.genfromtxt('build/data.txt', unpack=True)

fig, ax = plt.subplots()
ax.plot(N, mean_r, 'x--')
ax.set_xlabel('N')
ax.set_ylabel('r')
fig.tight_layout(pad=0)
fig.savefig('build/plot_01.pdf')
