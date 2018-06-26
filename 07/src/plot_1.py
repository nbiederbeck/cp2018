import numpy as np
import matplotlib.pyplot as plt

class plotter:
    def __init__(self, path):
        data = np.genfromtxt(path, delimiter=';')
        self.T = data[0,0]
        self.r_i = data[1:,0]
        self.v_i = data[:,1]

    def make_plot(self, path, title):
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(np.linspace(0,self.T,len(self.r_i)), self.r_i, label='r(t)')
        ax.plot(np.linspace(0,self.T,len(self.v_i)), self.v_i, label='v(t)')
        ax.set_xlabel('time')
        ax.set_ylabel('Amplitude')
        ax.legend(loc='best')
        ax.set_title(title)
        fig.tight_layout(pad=0)
        fig.savefig(path)

def main():
    p_euler = plotter('build/euler.txt')
    p_euler.make_plot('build/euler.pdf', 'Euler Algo')

if __name__ == '__main__':
    main()
