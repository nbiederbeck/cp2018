import numpy as np
import matplotlib.pyplot as plt


def plot_theta_time():
    fig, axes = plt.subplots(nrows=3, figsize=(4, 12))

    for i, choice in enumerate(["periodic", "quasi", "chaos"]):
        theta1, theta2, theta_1, theta_2, epot, ekin = np.genfromtxt(
            "build/poincare_data_{}.txt".format(choice), unpack=True
        )

        axes[i].scatter(((np.pi + theta1) % (2 * np.pi)) - np.pi, theta_1, s=1)
        axes[i].set_xlabel(r"$\theta_1$")
        axes[i].set_ylabel(r"$\dot\theta_1$")
        axes[i].set_title(choice)

    fig.tight_layout()
    fig.savefig("build/poincare_a.png", dpi=200)


def main():
    print("src/plot_poincare_a.py:  Plotting (a)")
    plot_theta_time()
    print("src/plot_poincare_a.py:  Done")


if __name__ == "__main__":
    main()
