import numpy as np
import matplotlib.pyplot as plt

b, c, rek = np.genfromtxt('build/1e.txt', delimiter=" ", unpack=True)

fig = plt.figure()
ax = fig.add_subplot(111)
ax.imshow(rek.reshape(15,15), extent=[1,15,1,15])
ax.set_title('Task')
fig.tight_layout(pad=0)
fig.savefig('build/plot_01e.png')
plt.close()
