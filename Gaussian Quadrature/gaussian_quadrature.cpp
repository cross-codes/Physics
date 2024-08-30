#include <bits/stdc++.h>

/**
 * Real-valued function
 *
 * Code implementation for any real-valued single-variable function.
 *
 * @param x (double) The argument of the function.
 * @return (double) The value of the function.
 */
long double f(long double x) { return exp(std::pow(x, 2)); }

int main() {
  // Data from the table corresponding to a three point division
  // Refer to https://classroom.google.com/u/1/c/NzAzMTAxNjU0MDcz

  // Abscissa
  long double e[5] = {0, -0.5384693101056831, 0.5384693101056831,
                      -0.9061798459386640, 0.9061798459386640};
  // Weights
  long double w[5] = {0.5688888888888889, 0.4786286704993665,
                      0.4786286704993665, 0.2369268850561891,
                      0.2369268850561891};

  long double a, b;

  std::cout << "Enter the lower bound of the integral (a): ";
  std::cin >> a;

  std::cout << "Enter the upper bound of the integral (b): ";
  std::cin >> b;

  long double sum = 0;

  for (int i = 0; i < 5; i++) {
    long double xi = ((b - a) * e[i] + (b + a)) / 2.0;
    sum += w[i] * f(xi);
  }

  std::cout << "Approximate value of the integral: " << std::setprecision(17)
            << ((b - a) / 2.0) * sum << std::endl;

  return 0;
}
