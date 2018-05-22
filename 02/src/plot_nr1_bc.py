import numpy as np
import matplotlib.pyplot as plt

data = {"eins": None, "zwei": None, "drei": None, "vier": None}
for label in data.keys():
    data[label] = np.genfromtxt("build/" + label + ".txt", unpack=True)

# b)
print("Plotting (1a) ...")
fig = plt.figure()
i = 221
for label in data.keys():
    ax = fig.add_subplot(i)
    ax.hist(data[label], bins=10, histtype="step", density=True)
    ax.set_title(label)
    i += 1
fig.tight_layout(pad=0)
fig.savefig("build/plot_01a.png")
plt.close()

# c)
print("Plotting (1b) ...")
fig = plt.figure()
i = 221
for label in data.keys():
    ax = fig.add_subplot(i)
    ax.hist2d(data[label][0::2], data[label][1::2], bins=100)
    ax.set_title(label)
    i += 1
fig.tight_layout(pad=0)
fig.savefig("build/plot_01b.png")
