import numpy as np
import matplotlib.pyplot as plt

ran = [0, 1]
kbT = [1, 2.27, 3]


def main():
    for r in ran:
        energy_files = []
        for k in kbT:
            energy_files.append(
                "build/02_Energie_ran_{r}_kbT_{k}.txt".format(r=r, k=k)
            )
        plot(energy_files, r)

def plot(energy_files, ran):
    filename = "build/energy_ran_{r}.png".format(r=ran)
    print("plot {}".format(filename))

    energies = []
    for f in energy_files:
        e = np.genfromtxt(f, delimiter=",")
        e = e[:-1]
        energies.append(e)

    fig, ax = plt.subplots()

    for e, k in zip(energies, [1, 2.27, 3]):
        ax.plot(range(len(e)), e, label=r"$k_BT=${}".format(k))

    ax.set_xlabel("Sweeps")
    ax.set_ylabel("e(t)")
    ax.set_xscale("log")
    ax.legend()

    ax.set_title(
        r"Initially {} Spins".format("Aligned" if ran == 0 else "Random")
    )
    fig.tight_layout()
    fig.savefig(filename)


if __name__ == "__main__":
    main()
