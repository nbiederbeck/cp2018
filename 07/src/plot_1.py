import numpy as np
import matplotlib.pyplot as plt

s_euler= np.genfromtxt('./build/euler.txt', delimiter=';')

T = s_euler[0,0]
r_i = s_euler[1:,0]
v_i = s_euler[:,1]

fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(np.linspace(0,T,len(r_i)), r_i, label='r(t)')
ax.plot(np.linspace(0,T,len(v_i)), v_i, label='v(t)')
ax.legend(loc='best')
fig.savefig('build/euler.pdf')
