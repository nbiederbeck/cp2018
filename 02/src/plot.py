import numpy as np
import matplotlib.pyplot as plt

def b(rs):
    """Untersuche den Generator für verschiedene Startwerte."""
    for r in rs:
        fig, ax = plt.subplots()
        ax.hist(rs[r], bins=10, density=True, histtype='step')
        ax.set_title('Linear Kongruenter Generator {}'.format(r[1]))
        ax.set_xlim([0, 1])
        ax.set_xlabel('r')
        ax.set_ylabel('# / N')
        fig.tight_layout(pad=0)
        fig.savefig('build/{}.pdf'.format(r))

def c(rs):
    """Untersuche den Generator auf Korrelationen."""
    for r in rs:
        fig, ax = plt.subplots()
        x = rs[r][2::2]
        y = rs[r][1::2]
        ax.hist2d(x, y)
        ax.set_title('Korrelationen Generator {}'.format(r[1]))
        ax.set_xlim([0, 1])
        ax.set_ylim([0, 1])
        ax.set_xlabel('')
        ax.set_ylabel('')
        fig.tight_layout(pad=0)
        fig.savefig('build/corr_{}.pdf'.format(r))


def main():
    r = np.genfromtxt("build/data.txt")

    rs = dict(
        r1 = r[:10001],
        r2 = r[10001:20002],
        r3 = r[20002:30003],
        r4 = r[30003:40004],
    )
    b(rs)
    c(rs)

if __name__ == '__main__':
    main()
