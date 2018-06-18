import numpy as np
import matplotlib.pyplot as plt

s_euler= np.genfromtxt('./build/euler.txt', delimiter=';')

r_i = s_euler[:,0]
v_i = s_euler[:,1]

fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(range(len(r_i)), r_i, label='r(t)')
ax.plot(range(len(v_i)), v_i, label='v(t)')
ax.legend(loc='best')
fig.savefig('build/euler.pdf')
