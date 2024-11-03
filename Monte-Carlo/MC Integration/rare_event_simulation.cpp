#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

/**
 * Problem statement: Compute P(Z >= 4)
 * Approach: Importance sampling
 * Sampling distribution: e^(-x-4) for x >= 4, else 0
 */

std::random_device rd{};
std::mt19937_64 gen{rd()};

long double q(long double x) {
  if (x < 4)
    return 0;
  return exp(-x + 4);
}

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

long double gen_sample_random(long double u) { return 4 - log(1 - u); }

long double importance_summand(long double x) {
  return (exp(-pow(x, 2) / 2) * (1 / sqrt(2 * M_PI))) / q(x);
}

int32_t main() {
  long double sum = 0.0L;
  for (int i = 0; i < 1e6; i++) {
    long double x = gen_sample_random(gen_uniform_random(0, 1));
    sum += importance_summand(x);
  }

  std::cout << "Estimated value of probability: " << sum / 1e6 << "\n";

  return 0;
}
