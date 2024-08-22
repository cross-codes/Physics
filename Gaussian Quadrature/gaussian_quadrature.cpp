#include <bits/stdc++.h>

/**
 * Real-valued function
 *
 * Code implementation for any real-valued single-variable function.
 *
 * @param x (double) The argument of the function.
 * @return (double) The value of the function.
 */
long double f(long double x) { return (9.80 * 8) * (1.0 - exp(-x / 8.0)); }

int main() {
  // Data from the table corresponding to a three point division
  // Refer to https://classroom.google.com/u/1/c/NzAzMTAxNjU0MDcz
  long double c[3] = {0.55555555555556, 0.88888888888889, 0.55555555555556};
  long double x[3] = {+0.7745966692414834, 0, -0.7745966692414834};

  long double a, b;

  std::cout << "Enter the lower bound of the integral (a): ";
  std::cin >> a;

  std::cout << "Enter the upper bound of the integral (b): ";
  std::cin >> b;

  long double sum = 0;

  for (int i = 0; i < 3; i++) {
    long double xmod = ((b - a) * x[i] + (b + a)) / 2.0;
    sum += c[i] * ((b - a) / 2.0) * f(xmod);
  }

  std::cout << "Approximate value of the integral: " << std::setprecision(17)
            << sum << std::endl;

  return 0;
}
