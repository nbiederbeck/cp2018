import numpy as np
import matplotlib.pyplot as plt

class lattice:
    def __init__(self, filename):
        self.read_filename = filename
        self.data = np.genfromtxt(self.read_filename)

    
    def plot_energy(self, filename,scale='linear'):
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(np.linspace(1,self.data.size,self.data.size),
                self.data)
        ax.set_xscale(scale)
        fig.tight_layout()
        fig.savefig(filename)
        plt.close()

if __name__ == '__main__':
    energy2 = lattice("build/energie.txt")
    energy2.plot_energy('build/energy2.pdf')
    energy3 = lattice("build/energie3.txt")
    energy3.plot_energy('build/energy3.pdf')
    energy6 = lattice("build/energie6.txt")
    energy6.plot_energy('build/energy6.pdf')
    energy20 = lattice("build/energie20.txt")
    energy20.plot_energy('build/energy20.pdf')
