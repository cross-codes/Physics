#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

double gen_normal_random(double mean, double stdev) {
  std::normal_distribution<double> distribution(mean, stdev);
  return distribution(gen);
}

double gen_special_random_classical(double u) { return -log(1 - u); }

double gen_special_random_importance(double u, double alpha) {
  return pow(u, (1.0 / 1 - alpha));
}

long double classical_summand_1(long double x, double alpha) {
  return pow(x, -alpha) * exp(-x);
}

long double classical_summand_2(long double x, double alpha) {
  if (x > 1 || x < 0)
    return 0;
  return pow(x, -alpha);
}

long double importance_summand_1(long double x, double alpha) {
  if (x > 1 || x < 0)
    return 0;
  return pow(x, -alpha) * exp(-x) /
         (exp(-pow(x, 2) / 2) * 1 / (sqrt(2 * M_PI)));
}

long double importance_summand_2(long double x, double alpha) {
  return exp(-x) / (1 - alpha);
}

int32_t main() {
  // Classical method: Integrand unchanged

  double alpha = 0.4;

  long double sum = 0.0L;
  for (int i = 0; i < 1e6; i++) {
    double x = gen_uniform_random(0, 1);
    sum += classical_summand_1(x, alpha);
  }

  std::cout << "Estimated value of integral (CMC): " << sum / 1e6 << "\n";

  std::cout.flush();

  // Classical method: Domain set to infinity, distribution to e^-x

  sum = 0.0L;
  for (int i = 0; i < 1e6; i++) {
    double u = gen_uniform_random(0, 1);
    double x = gen_special_random_classical(u);
    sum += classical_summand_2(x, alpha);
  }

  std::cout << "Estimated value of integral (CMC 2): " << sum / 1e6 << "\n";

  std::cout.flush();

  // Autonormalized importance sampling from N(0, 1)
  sum = 0.0L;
  for (int i = 0; i < 1e6; i++) {
    double x = gen_normal_random(0, 1);
    sum += importance_summand_1(x, alpha);
  }

  std::cout << "Estimated value of integral (IM): " << sum / 1e6 << "\n";

  std::cout.flush();

  // Importance sampling from x^-alpha (normalized)

  sum = 0.0L;
  for (int i = 0; i < 1e6; i++) {
    double u = gen_uniform_random(0, 1);
    double x = gen_special_random_importance(u, alpha);
    sum += importance_summand_2(x, alpha);
  }

  std::cout << "Estimated value of integral (IM 2): " << sum / 1e6 << "\n";

  std::cout.flush();

  return 0;
}
