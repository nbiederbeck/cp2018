import numpy as np
import matplotlib.pyplot as plt

first = np.genfromtxt("build/02_init.txt", delimiter=",")
n, m = first.shape
first = first[1:n - 1, 1:m - 2]

final = np.genfromtxt("build/02_sweep.txt", delimiter=",")
n, m = final.shape
final = final[1:n - 1, 1:m - 2]


# # Display Lattice After MC
fig = plt.figure()
fig.set_size_inches(10, 4)
ax_first = fig.add_subplot(121)
ax_final = fig.add_subplot(122)

cmap = plt.get_cmap("binary", 2)

im_first = ax_first.imshow(first, cmap=cmap)
im_final = ax_final.imshow(final, cmap=cmap)

cbar = fig.colorbar(im_first)
cbar.set_ticks([-1, 1])
cbar.ax.set_ylabel("Spin")

fig.tight_layout()
fig.savefig("build/cpp_sweep.png")
