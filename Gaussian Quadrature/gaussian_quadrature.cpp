#include <bits/stdc++.h>

/**
 * Real-valued function
 *
 * Code implementation for any real-valued single-variable function.
 *
 * @param x (double) The argument of the function.
 * @return (double) The value of the function.
 */
long double f(long double x) { return 1 / (1 + std::pow(x, 2)); }

int main() {
  // Data from the table corresponding to a ten point division
  // Refer to https://classroom.google.com/u/1/c/NzAzMTAxNjU0MDcz

  // Abscissa
  long double e[10] = {-0.97390653, -0.86506337, -0.67940957, -0.43339539,
                       -0.14887434, 0.14887434,  0.43339539,  0.67940957,
                       0.86506337,  0.97390653};
  // Weights
  long double w[10] = {0.06667134, 0.14945135, 0.21908636, 0.26926672,
                       0.29552422, 0.29552422, 0.26926672, 0.21908636,
                       0.14945135, 0.06667134};

  long double a, b;

  std::cout << "Enter the lower bound of the integral (a): ";
  std::cin >> a;

  std::cout << "Enter the upper bound of the integral (b): ";
  std::cin >> b;

  long double sum = 0;

  for (int i = 0; i < (int)(sizeof(e) / sizeof(e[0])); i++) {
    long double xi = ((b - a) * e[i] + (b + a)) / 2.0;
    sum += w[i] * f(xi);
  }

  std::cout << "Approximate value of the integral: " << std::setprecision(17)
            << ((b - a) / 2.0) * sum << std::endl;

  return 0;
}
