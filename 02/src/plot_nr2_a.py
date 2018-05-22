import numpy as np
import matplotlib.pyplot as plt

data, Data = np.genfromtxt("build/task2aI.txt", delimiter=";", unpack=True)

# c)
print("Plotting (2a) ...")
x = np.linspace(0, np.pi * 0.5, 50)
fig = plt.figure()
Data = Data[Data >= 0]

ax = fig.add_subplot(211)
n, bins, patches = ax.hist(data, bins=100, histtype="step", density=True, label="(i)")
N, Bins, Patches = ax.hist(Data, bins=100, histtype="step", density=True, label="(ii)")
ax.plot(x, np.cos(x), alpha=0.7, label="cos(x)")
ax.legend(loc="upper right")
ax.set_title("Histogram")

bins = bins[:-1]
Bins = Bins[:-1]
bins += (bins[1] - bins[0]) / 2
Bins += (Bins[1] - Bins[0]) / 2

ax2 = fig.add_subplot(212)
ax2.plot(bins, n - np.cos(bins), label="(i)-cos(x)")
ax2.plot(Bins, N - np.cos(Bins), label="(ii)-cos(x)")
ax2.legend(loc="lower right")
ax2.set_title("Diffs")
ax2.grid(True)

fig.tight_layout(pad=0)
fig.savefig("build/plot_02a.png")
plt.close()
