#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

/**
 * Estimating the integral of x^α * exp(-x) from 0 to 1
 * This program uses the CGL algorithm
 */

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_normal_random(double mean, double stdev) {
  std::normal_distribution<double> distribution(mean, stdev);
  return distribution(gen);
}

double f(long double x, double alpha) { return pow(x, alpha) * exp(-x); }

double p(long double x) {
  if (x > 1 || x < 0)
    return 0.0;
  return 1;
}

double q(long double x) { return exp(-pow(x, 2) / 2) * 1 / (sqrt(2 * M_PI)); }

double fp_by_q(long double x, double alpha) {
  // For some reason I need to do this
  if (p(x) == 0)
    return 0;
  return f(x, alpha) * p(x) / q(x);
}

int32_t main() {
  double alpha = -0.2;

  long double M = 0.0L, P = 0.0L;

  std::ofstream data_file("/tmp/cgl.dat");

  data_file << 0 << " " << 0.0L << " " << 0.0L << "\n";

  for (int i = 1; i <= 1e6; i++) {
    double rand_val = gen_normal_random(0, 1);
    long double summand = fp_by_q(rand_val, alpha);
    long double u = summand - M;

    M += u / i;
    P = ((double)(i - 1) / i) * (P + u * u / i);

    data_file << i << " " << M << " " << P / i << "\n";
  }

  data_file.close();

  std::cout << "Final value of integral estimator: " << M << "\n";

  std::cout << "Final value of variance estimator: " << P / 1e6 << "\n";

  system("gnuplot -p plot.gp");

  return 0;
}
