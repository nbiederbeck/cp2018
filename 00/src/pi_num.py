from numpy.random import rand


def main():
    N = 100000

    xy = rand(N, 2)

    r = xy[:,0] ** 2 + xy[:,1]**2

    n = sum(r < 1)

    pi_est = 4 * n / float(N)

    print(pi_est)


if __name__ == '__main__':
    main()
