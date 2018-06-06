import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt('build/task2c.txt', unpack=True)

# d)
fig = plt.figure()
ax = fig.add_subplot(111)
ax.hist(data, bins=30, histtype='step', normed=True)
fig.tight_layout(pad=0)
fig.savefig('build/plot_02c.png')
