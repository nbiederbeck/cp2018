import numpy as np
import matplotlib.pyplot as plt


def plot_theta_time():
    fig, axes = plt.subplots(nrows=3, figsize=(8, 12))

    for i, choice in enumerate(["periodic", "quasi", "chaos"]):
        theta1, theta2, theta_1, theta_2, epot, ekin = np.genfromtxt(
            "build/poincare_data_{}.txt".format(choice), unpack=True
        )
        theta1_dis, theta2_dis, theta_1_dis, theta_2_dis, epot_dis, ekin_dis = np.genfromtxt(
            "build/poincare_data_{}_disturbed.txt".format(choice), unpack=True
        )

        time = range(len(theta1))

        axes[i].plot(
            time,
            theta1 - theta1_dis,
            label=r"$\theta_1$",
        )
        axes[i].plot(
            time,
            theta2 - theta2_dis,
            label=r"$\theta_2$",
        )
        axes[i].plot(
            time,
            theta_1 - theta_1_dis,
            label=r"$\dot\theta_1$",
        )
        axes[i].plot(
            time,
            theta_2 - theta_2_dis,
            label=r"$\dot\theta_2$",
        )
        axes[i].legend(loc="lower left")
        axes[i].set_xlabel(r"$t$")
        axes[i].set_ylabel(r"start parameter - disturbed parameter")
        axes[i].set_title(choice)

    fig.tight_layout()
    fig.savefig("build/poincare_b.png", dpi=200)


def main():
    print("src/plot_poincare_b.py:  Plotting (b)")
    plot_theta_time()
    print("src/plot_poincare_b.py:  Done")


if __name__ == "__main__":
    main()
