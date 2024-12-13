#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

int32_t main() {
  int matching = 0;
  for (int iterations = 1; iterations < 1e6; iterations++) {
    double x = gen_uniform_random(0, 1);
    double y = gen_uniform_random(0, 1);
    if (x * x + y * y <= 1)
      matching++;
  }

  std::cout << "Estimated value of PI: " << 4 * matching / 1e6 << "\n";
}
