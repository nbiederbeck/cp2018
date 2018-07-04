import numpy as np
import matplotlib.pyplot as plt


def plot_theta_time():
    fig, axes = plt.subplots(nrows=3, figsize=(8, 12))

    for i, energy, xlims in zip([0,1,2], [1,10,70], [0.3,2,100]):
        theta1, theta_1 = np.genfromtxt(
            "build/poincare_c_{}.txt".format(energy), unpack=True
        )

        axes[i].scatter(
            theta1,
            theta_1,
            s=0.3, 
        )
        axes[i].set_xlim([-xlims, xlims])
        axes[i].set_xlabel(r"$\theta_1$")
        axes[i].set_ylabel(r"$\dot\theta_1$")
        axes[i].set_title('Energie = {}$\,$J'.format(energy))

    fig.tight_layout()
    fig.savefig("build/poincare_c.png", dpi=200)


def main():
    print("src/plot_poincare_c.py:  Plotting (c)")
    plot_theta_time()
    print("src/plot_poincare_c.py:  Done")


if __name__ == "__main__":
    main()
