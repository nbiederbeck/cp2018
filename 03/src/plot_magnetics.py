import numpy as np
import matplotlib.pyplot as plt

ran = [0, 1]
kbT = [1, 2.27, 3]


def main():
    for r in ran:
        # magnetic_files = []
        # energy_files = []
        for k in kbT:
            # magnetic_files.append(
            magnetic_file = "build/02_Sum_Spin_ran_{r}_kbT_{k}.txt".format(
                r=r, k=k
            )
            # )
            # energy_files.append(
            energy_file = "build/02_Energie_ran_{r}_kbT_{k}.txt".format(
                r=r, k=k
            )
            # )
            plot(magnetic_file, energy_file, r, k)


def plot(magnetic_file, energy_file, r, k):
    filename = "build/magnetic_ran_{r}_kbT_{k}.png".format(r=r, k=k)
    print("plot {}".format(filename))

    e = np.genfromtxt(energy_file, delimiter=",")
    e = e[:-1]
    m = np.genfromtxt(magnetic_file, delimiter=",")
    m = m[:-1]
    am = np.abs(m)

    fig, ax = plt.subplots()

    ax.plot(range(len(e)), e, label=r"Energie".format(k))
    ax.plot(range(len(m)), m, label=r"Magnetisierung".format(k))
    ax.plot(range(len(am)), am, label=r"Absolute Magnetisierung".format(k))

    ax.set_title(
        r"Initially {} Spins, $k_BT=${}".format(
            "Aligned" if r == 0 else "Random", k
        )
    )

    ax.set_xlabel("Sweeps")
    ax.set_ylabel("e(t)")
    ax.set_xscale("log")
    ax.legend()

    fig.tight_layout(pad=0)
    fig.savefig(filename)


if __name__ == "__main__":
    main()
