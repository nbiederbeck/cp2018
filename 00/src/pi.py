from numpy.random import rand


def main():
    n = 0.0
    N = 100000

    for i in range(N):
        x = rand()
        y = rand()
        if x**2 + y**2 < 1:
            n += 1

    pi_est = 4 * n / N

    print(pi_est)


if __name__ == '__main__':
    main()
