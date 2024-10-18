#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937 gen{rd()};

long double integrand(long double x, int alpha) {
  return pow(x, -alpha) * exp(-x);
}

long double importance_integrand(long double x, int alpha) {
  if (x > 1 || x < 0)
    return 0;
  return integrand(x, alpha) / (exp(-pow(x, 2) / 2) * 1 / (sqrt(2 * M_PI)));
}

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

double gen_normal_random(double mean, double stdev) {
  std::normal_distribution<double> distribution(mean, stdev);
  return distribution(gen);
}

int32_t main() {
  // Classical method

  double alpha = 0.5;
  long a = 0L, b = 1L;

  long double sum = 0.0L;
  for (int i = 0; i < 1e6; i++) {
    double x = gen_uniform_random(a, b);
    sum += integrand(x, alpha);
  }

  std::cout << "Estimated value of integral (CMC): " << (b - a) * sum / 1e6
            << "\n";

  std::cout.flush();

  // Autonormalized importance sampling from N(0, 1)
  sum = 0.0L;
  for (int i = 0; i < 1e6; i++) {
    double x = gen_normal_random(0, 1);
    sum += importance_integrand(x, alpha);
  }

  std::cout << "Estimated value of integral (IM): " << sum / 1e6 << "\n";

  return 0;
}
