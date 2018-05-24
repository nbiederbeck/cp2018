import numpy as np
import matplotlib.pyplot as plt

init = np.genfromtxt("build/test.txt")
n, m = init.shape

lattice = []
for x in range(int(n/m)):
    lattice.append(init[m*x:m*(x+1), :m])

q = len(np.unique(init))
def plot_lattice(lattice, filename):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    grid = np.meshgrid(
            np.linspace(0,1,m),
            np.linspace(0,1,m)
            )
    lattice = ax.pcolormesh(*grid, 
            lattice[999], cmap=plt.get_cmap('YlGn'))
    cbar = fig.colorbar(lattice)
    cbar.set_ticks([0, q])
    cbar.ax.set_ylabel("Spin")
    fig.tight_layout()
    fig.savefig(filename)
