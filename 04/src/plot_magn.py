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

if __name__ == '__main__':
    magn = lattice("build/magn.txt")
    magn.read_magn()
    magn.plot_magn('build/magn.pdf')
