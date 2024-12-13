#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

double x(double u) { return (-1.0 / 4 * log(1 - u)); }

int32_t main() {
  for (int i = 0; i < 10; i++) {
    std::cout << x(gen_uniform_random(0, 1)) << "\n";
  }
}
