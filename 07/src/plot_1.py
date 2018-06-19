import numpy as np
import matplotlib.pyplot as plt

class plotter:
    def __init__(self, path):
        # data = np.genfromtxt(path, delimiter=';')
        self.T = np.genfromtxt(path+'T.txt')
        self.r_i = np.genfromtxt(path+'r_i.txt')
        self.v_i = np.genfromtxt(path+'v_i.txt')
        # self.r_i = data[1:,0]
        # self.v_i = data[:,1]

    def make_plot(self, path, title, dim):
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(np.linspace(0,self.T,len(self.r_i[dim,:])), self.r_i[dim,:], label='r(t)')
        ax.plot(np.linspace(0,self.T,len(self.v_i[dim,:])), self.v_i[dim,:], label='v(t)')
        ax.set_xlabel('time')
        ax.set_ylabel('Amplitude')
        ax.legend(loc='best')
        ax.set_title(title)
        ax.grid()
        fig.tight_layout(pad=0)
        fig.savefig(path)

def main():
    p_euler = plotter('build/euler/')
    p_euler.make_plot('build/euler.png', 'Euler Verfahren', 0)
    p_runge= plotter('build/runge/')
    p_runge.make_plot('build/runge.png', 'Runge Verfahren', 0)

if __name__ == '__main__':
    main()
