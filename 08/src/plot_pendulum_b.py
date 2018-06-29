import numpy as np
import matplotlib.pyplot as plt


def plot_theta_time():
    theta1, theta2, theta_1, theta_2 = np.genfromtxt("build/pendulum_data_b.txt", unpack=True)
    time = range(len(theta1))

    fig, (ax1, ax2) = plt.subplots(nrows=2)

    ax1.plot(time, theta1, label=r"$\theta_1$")
    ax1.plot(time, theta2, label=r"$\theta_2$")
    ax1.set_xlabel(r"$t$")
    ax1.set_ylabel(r"$A(t)$")
    ax1.legend()

    ax2.plot(time, theta_1, label=r"$\dot\theta_1$")
    ax2.plot(time, theta_2, label=r"$\dot\theta_2$")
    ax2.set_xlabel(r"$t$")
    ax2.set_ylabel(r"$A(t)$")
    ax2.legend()

    fig.tight_layout()
    fig.savefig("build/pendulum_b.png", dpi=200)


def plot_xy():
    theta1, theta2, theta_1, theta_2 = np.genfromtxt("build/pendulum_data_b.txt", unpack=True)

    x1, y1 = np.sin(theta1), - np.cos(theta1)
    x2, y2 = x1 + np.sin(theta2), y1 - np.cos(theta2)

    fig, ax = plt.subplots()
    ax.plot(x1, y1, label=r"Pendel 1")
    ax.plot(x2, y2, label=r"Pendel 2")
    ax.scatter(x1[0], y1[0], marker="x")
    ax.scatter(x2[0], y2[0], marker="x")
    ax.set_xlabel(r"$x$")
    ax.set_ylabel(r"$y$")
    ax.legend()
    ax.set_ylim([-2.2, 0])
    ax.set_xlim([-1, 1])
    ax.set_aspect(1)
    fig.tight_layout()
    fig.savefig("build/pendulum_xy_b.png", dpi=200)


def main():
    print("src/plot_pendulum_b.py:  Plotting (b)")
    plot_theta_time()
    plot_xy()
    print("src/plot_pendulum_b.py:  Done")


if __name__ == "__main__":
    main()
