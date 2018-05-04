import numpy as np
import matplotlib.pyplot as plt

data = {"Eins": None, "Zwei": None}
for label in data.keys():
    data[label] = np.genfromtxt("build/" + label + ".txt", unpack=True)

# d)
print("Plotting (1d) ...")
fig = plt.figure()
i = 221
for label in data.keys():
    ax = fig.add_subplot(i)
    ax.hist(data[label], bins=10, histtype="step", density=True)
    ax.set_title(label)
    i += 1

i = 223
for label in data.keys():
    ax = fig.add_subplot(i)
    ax.hist2d(data[label][0::2], data[label][1::2], bins=20)
    ax.set_title(label)
    i += 1
fig.tight_layout(pad=0)
fig.savefig("build/plot_01d.png")
