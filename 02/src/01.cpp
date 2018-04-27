#include <cmath>
#include <iostream>
#include <array>

std::array<double, 10000+1> linear_congruent_generator(
        int32_t r0, int32_t a, int32_t c, int32_t m, int32_t N
    ) {

    std::array<double, 10000+1> numbers = {};
    numbers[0] = r0;

    for (int i = 0; i < N; ++i) {
        numbers[i+1] = static_cast<double> (static_cast<int>(a * numbers[i] + c) % static_cast<int>(m));
    }
    for (int i = 0; i <= N; ++i) {
        numbers[i] /= m;
    }
    for (int i = 0; i <= N; ++i) {
        printf("%f\n", numbers[i]);
    }
    return numbers;
}

int main() {
    printf("\n# (i)\n# ===\n");
    std::array<double, 10000+1> numbers_i = linear_congruent_generator(1234, 20, 120, 6075, 10000);
    printf("\n# (ii)\n# ====\n");
    std::array<double, 10000+1> numbers_ii = linear_congruent_generator(1234, 137, 187, 256, 10000);
    printf("\n# (iii)\n# =====\n");
    std::array<double, 10000+1> numbers_iii = linear_congruent_generator(123456789, 65539, 0, 2147483648, 10000);
    printf("\n# (iv)\n# ====\n");
    std::array<double, 10000+1> numbers_iv = linear_congruent_generator(1234, 16807, 0, 2147483647, 10000);

    // std::fstream fs;
    // fs.open("build/data.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    // fs << "# N mean_r\n";
    // fs << N << " "
    //    << mean << "\n";
    // fs.close();

    return 0;
}
