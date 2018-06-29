import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


fig, ax = plt.subplots()
ax.grid()
ax.set_xlim([0, 2*np.pi])
ax.set_ylim([-1.1, 1.1])
line, = ax.plot([], [], lw=2)


xdata, ydata = [], []
def init():
    line.set_data(xdata, ydata)
    return (line,)

N_frames = 100
def animate(i):
    x = np.linspace(0, 2*np.pi, 101)
    y = i / N_frames * np.sin(x)
    line.set_data(x, y)
    return line,

ani = animation.FuncAnimation(
    fig, animate, frames=N_frames, blit=True, interval=20, init_func=init,
)

plt.show()
