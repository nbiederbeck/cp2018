import numpy as np
import matplotlib.pyplot as plt

ran = [0, 1]
kbT = [1, 2.27, 3]
snapshots = ["init", "sweep"]


def main():
    for r in ran:
        for k in kbT:
            init = "build/02_init_ran_{r}_kbT_{k}.txt".format(r=r, k=k)
            final = "build/02_sweep_ran_{r}_kbT_{k}.txt".format(r=r, k=k)
            plot(init, final, r, k)


def plot(init_file, final_file, ran, kbT):
    if kbT == 2.27:
        kbT *= 100
    filename = "build/lattice_ran_{r}_kbT_{k:.0f}.png".format(r=ran, k=kbT)
    if kbT == 227:
        kbT /= 100
    print("plot {}".format(filename))
    init = np.genfromtxt(init_file, delimiter=",")
    n, m = init.shape
    init = init[1:n - 1, 1:m - 2]

    final = np.genfromtxt(final_file, delimiter=",")
    n, m = final.shape
    final = final[1:n - 1, 1:m - 2]

    fig = plt.figure()
    fig.set_size_inches(9.5, 4)

    ax_first = fig.add_subplot(121)
    ax_final = fig.add_subplot(122)

    cmap = plt.get_cmap("binary", 2)

    im_first = ax_first.imshow(init, cmap=cmap)
    ax_first.set_title("Initialized Lattice.", fontsize=10)
    ax_first.set_xlabel("x")
    ax_first.set_ylabel("y")

    im_final = ax_final.imshow(final, cmap=cmap)
    ax_final.set_title("Lattice After MC.", fontsize=10)
    ax_final.set_xlabel("x")
    ax_final.set_ylabel("y")

    cbar = fig.colorbar(im_first)
    cbar.set_ticks([-1, 1])
    cbar.ax.set_ylabel("Spin")

    fig.suptitle(r"ISING MC, $k_BT=${k}".format(k=kbT), fontsize=16)
    fig.tight_layout()
    fig.savefig(filename)


if __name__ == "__main__":
    main()
