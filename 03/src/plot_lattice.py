import numpy as np
import matplotlib.pyplot as plt


init_file = "build/02_init.txt"
final_file = "build/02_sweep.txt"

init = np.genfromtxt(init_file, delimiter=",")
n, m = init.shape
init = init[1:n - 1, 1:m - 2]

final = np.genfromtxt(final_file, delimiter=",")
n, m = final.shape
final = final[1:n - 1, 1:m - 2]


fig = plt.figure()
fig.set_size_inches(10, 4)

ax_first = fig.add_subplot(121)
ax_final = fig.add_subplot(122)

cmap = plt.get_cmap("binary", 2)

im_first = ax_first.imshow(init, cmap=cmap)
ax_first.set_title("Randomly initlialized lattice.")
ax_first.set_xlabel("x")
ax_first.set_ylabel("y")

im_final = ax_final.imshow(final, cmap=cmap)
ax_final.set_title("Lattice after MC.")
ax_final.set_xlabel("x")
ax_final.set_ylabel("y")

cbar = fig.colorbar(im_first)
cbar.set_ticks([-1, 1])
cbar.ax.set_ylabel("Spin")

fig.tight_layout(pad=0)
fig.savefig("build/cpp_sweep.png")
