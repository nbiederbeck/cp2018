import numpy as np
import matplotlib.pyplot as plt

ran = [0, 1]
kbT = [1, 2.27, 3]


def main():
    for r in ran:
        energy_files = []
        energy_2_files = []
        for k in kbT:
            energy_files.append(
                "build/02_Energie_ran_{r}_kbT_{k}.txt".format(r=r, k=k)
            )
            energy_2_files.append(
                "build/02_Energie_2_ran_{r}_kbT_{k}.txt".format(r=r, k=k)
            )
        plot(energy_files, energy_2_files, r)


def plot(energy_files, energy_2_files, ran):
    filename = "build/energy_2_ran_{r}.png".format(r=ran)
    print("plot {}".format(filename))

    specific_heats = []
    for f, F in zip(energy_files, energy_2_files):
        c = np.genfromtxt(f, delimiter=",")
        c2 = np.genfromtxt(F, delimiter=",")
        c = c[:-1]
        c2 = c2[:-1]
        specific_heats.append(c2 - c)

    fig, ax = plt.subplots()

    for e, k in zip(specific_heats, [1, 2.27, 3]):
        ax.plot(range(len(e)), e/(k**2)*1.38e-23, label=r"$k_BT=${}".format(k))

    ax.set_xlabel("Sweeps")
    ax.set_ylabel(r"$c(T) = \frac{<H^2> - <H>^2}{(k_B T^2 N)}$")
    ax.set_xscale("log")
    ax.legend()

    ax.set_title(
        r"Initially {} Spins".format("Aligned" if ran == 0 else "Random")
    )
    fig.tight_layout()
    fig.savefig(filename)


if __name__ == "__main__":
    main()
