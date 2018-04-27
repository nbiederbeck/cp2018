import numpy as np
def linear_congruent_generator(r0, a, c, m, N):
    """ $r_{n+1} = (ar_{n}+c)\mod{m}$ """
    numbers = []*N
    print(numbers)
    numbers[0] = r0
    for i in len(numbers):
        numbers[i+1] = (a * numbers[i] + c) % m
        print("{}: {}".format(i, numbers[i]))
    return numbers

def main():
    numbers = linear_congruent_generator(1234, 20, 120, 6075, 10)
    pass

if __name__ == "__main__":
    main()
