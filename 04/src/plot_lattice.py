import numpy as np
import matplotlib.pyplot as plt

class lattice:
    def __init__(self, filename):
        self.lattice = None
        self.m = None
        self.read_filename = filename

    def read_lattice(self):
        init = np.genfromtxt(self.read_filename)
        n, self.m = init.shape
        self.lattice = []
        for x in range(int(n/self.m)):
            self.lattice.append(init[self.m*x:self.m*(x+1), :self.m])
    
        return lattice, self.m
    
    
    def plot_lattice(self, num, filename):
        fig = plt.figure()
        ax = fig.add_subplot(111)
        grid = np.meshgrid(
                np.linspace(0,1,self.m),
                np.linspace(0,1,self.m)
                )
        lattice = ax.pcolormesh(*grid, 
                self.lattice[num], cmap=plt.get_cmap('YlGn'))
        cbar = fig.colorbar(lattice)
        # cbar.set_ticks([0, q])
        cbar.ax.set_ylabel("Spin")
        fig.tight_layout()
        fig.savefig(filename)

if __name__ == '__main__':
    lattice_q2 = lattice("build/q_2.txt")
    lattice_q3 = lattice("build/q_3.txt")
    lattice_q2.read_lattice()
    lattice_q3.read_lattice()
    for x in [0,30,100,250,999]:
        lattice_q2.plot_lattice(x, 'build/q_2_'+str(x)+'.pdf')
        lattice_q3.plot_lattice(x, 'build/q_3_'+str(x)+'.pdf')
