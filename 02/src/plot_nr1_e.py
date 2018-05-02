import numpy as np
import matplotlib.pyplot as plt

b, c, rek = np.genfromtxt("build/1e.txt", delimiter=" ", unpack=True)

print("Plotting (1e) ...")
fig = plt.figure()
ax = fig.add_subplot(111)
im = ax.pcolormesh(b.reshape(15, 15), c.reshape(15, 15), rek.reshape(15, 15))
ax.set_xlabel("b")
ax.set_ylabel("c")
ax.set_title("Task")
cbar = fig.colorbar(im)
cbar.ax.set_ylabel("Rekursionslaenge")
fig.tight_layout(pad=0)
fig.savefig("build/plot_01e.png")
plt.close()
