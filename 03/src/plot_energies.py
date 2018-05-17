import numpy as np
import matplotlib.pyplot as plt

energie1 = np.genfromtxt("build/02_Energie_ran_0_kbT_1.txt", delimiter=",")
energie2 = np.genfromtxt("build/02_Energie_ran_0_kbT_2.27.txt", delimiter=",")
energie3 = np.genfromtxt("build/02_Energie_ran_0_kbT_3.txt", delimiter=",")

n = 100
kbT = 1

energie1 = energie1[:-1] 
energie2 = energie2[:-1] 
energie3 = energie3[:-1] 

fig, ax = plt.subplots()
print(energie1)
ax.plot(range(len(energie1)), energie1, "--", label="Energie")
# ax.plot(range(len(energie2)), energie2, ".-", label="Energie")
# ax.plot(range(len(energie3)), energie3, ".", label="Energie")

ax.set_xlabel("Sweeps")
ax.set_ylabel("e(t), m(t), |m|(t)")
ax.set_xscale("log")
# ax.set_yscale("log")
ax.legend()

fig.tight_layout(pad=0)
fig.savefig("build/energies.png")
