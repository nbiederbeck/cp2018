
# coding: utf-8

# # Ising model using python

# Pseudo code
# ```python
# for every point in the grid:
#     energy = my spin * sum of all of the spins (+1 or -1) of neighboring points
#     if energy is improved by switching:
#         switch
#     else if we're particulalry unlucky
#         switch anyway
# ```

import numpy as np
import matplotlib.pyplot as plt

get_ipython().run_line_magic("matplotlib", "inline")


# Initialize Random Lattice
def init(n, m=None):
    if m is None:
        m = n
    field = np.random.choice([-1, 1], size=[n, m])  # Random Spins

    # Implement periodic lattice
    lattice = np.zeros([n + 2, m + 2])
    lattice[1:n + 1, 1:m + 1] = field
    lattice[:, 0] = lattice[:, m]
    lattice[:, m + 1] = lattice[:, 1]
    lattice[0, :] = lattice[n, :]
    lattice[n + 1, :] = lattice[1, :]
    lattice[0, 0] = lattice[0, m + 1] = lattice[n + 1, 0] = lattice[
        n + 1, m + 1
    ] = 0

    return field


# Implement Ising Model Steps
def step(f):
    n, m = f.shape

    for i in range(1, n - 1):
        for j in range(1, m - 1):
            e = f[i, j] * (
                f[i - 1, j] + f[i + 1, j] + f[i, j - 1] + f[i, j + 1]
            )
            # Change Spin According To Other Spins And Boltzmann
            # TODO: IMPLEMENT ME
            if e < f[i, j]:
                f[i, j] = np.sign(e) if np.sign(e) != 0 else 1
    return f


# Define Start Values
steps = 10
n = 10
f = init(n)

images = [f]

# Run Model, Save Every Step
for i in range(steps):
    images.append(step(images[-1].copy()))


# Display Lattice After MC
final = images[-1]

fig, ax = plt.subplots()

cmap = plt.get_cmap("binary", 2)

im = ax.imshow(final[1:n + 1, 1:n + 1], cmap=cmap)

cbar = fig.colorbar(im)
cbar.set_ticks([-1, 1])
cbar.ax.set_ylabel("Spin")

ax.set_title("Spinzustaende im Ising Modell")
fig.tight_layout()
fig
