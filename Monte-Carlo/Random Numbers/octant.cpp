#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

int32_t main() {
  // Here P(x, y, z) = 6 / PI if within the octant, and zero otherwise
  // We cannot divide by zero, so we instead take the average for cases where
  // this never happens at all (number_in_1)
  double sum_1 = 0;
  int number_in_1 = 0;
  for (int i = 0; i < 1e6; i++) {
    double x = gen_uniform_random(0, 1);
    double y = gen_uniform_random(0, 1);
    double z = gen_uniform_random(0, 1);

    if (x * x + y * y + z * z <= 1) {
      number_in_1++;
      double val = M_PI / 6;
      sum_1 += val;
    }
  }

  std::cout << "Estimated value (1): " << 8 * sum_1 / number_in_1 << "\n";

  // Here, we are not exactly estimating 0, 1 and 0, 1 for x and y ; We are
  // adding x^2 + y ^ 2 < 1 as well, so because we cannot divide by zero, we
  // do not consider such cases at all
  double sum_2 = 0;
  int number_in_2 = 1;
  for (int i = 0; i < 1e6; i++) {
    double x = gen_uniform_random(0, 1);
    double y = gen_uniform_random(0, 1);

    if (x * x + y * y <= 1) {
      number_in_2++;
      double val = sqrt(1 - x * x - y * y);
      sum_2 += val;
    }
  }

  std::cout << "Estimated value (2): " << 2 * M_PI * sum_2 / number_in_2
            << "\n";
}
