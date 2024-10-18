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

  double alpha;
  long a, b;
  std::cout << "Enter the value of the parameter (0 < α < 1): ";
  std::cin >> alpha;

  std::cout << "Enter the lower limit: ";
  std::cin >> a;

  std::cout << "Enter the upper limit: ";
  std::cin >> b;

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
