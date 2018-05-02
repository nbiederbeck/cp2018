import numpy as np
import matplotlib.pyplot as plt

data, Data = np.genfromtxt('build/task2aI.txt', delimiter=";", unpack=True)
print(data)
print(Data)
# b)
x = np.linspace(0,np.pi*0.5,50)
fig = plt.figure()
ax = fig.add_subplot(111)
ax.hist(data, bins=100)
# Data = Data[Data>=0]
# ax.hist(data, bins=100, histtype='step', normed=True)
# ax.hist(Data, bins=100, histtype='step', normed=True)
# ax.plot(x, np.cos(x))
ax.set_title('Task')
fig.tight_layout(pad=0)
fig.savefig('build/plot_02a.png')
plt.close()
