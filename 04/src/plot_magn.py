import numpy as np
import matplotlib.pyplot as plt

class lattice:
    def __init__(self, filename):
        self.read_filename = filename
        self.data =None

    def read_magn(self):
        self.data= np.genfromtxt(self.read_filename)
    
    def plot_magn(self, filename):
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(np.linspace(1,self.data.size,self.data.size),
                self.data)
        fig.tight_layout()
        fig.savefig(filename)
        plt.close()

if __name__ == '__main__':
    magn = lattice("build/magn.txt")
    magn.read_magn()
    magn.plot_magn('build/magn.pdf')
    magn3 = lattice("build/magn3.txt")
    magn3.read_magn()
    magn3.plot_magn('build/magn3.pdf')
    magn6 = lattice("build/magn6.txt")
    magn6.read_magn()
    magn6.plot_magn('build/magn6.pdf')
    magn20 = lattice("build/magn20.txt")
    magn20.read_magn()
    magn20.plot_magn('build/magn20.pdf')
