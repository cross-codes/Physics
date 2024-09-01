#include <bits/stdc++.h>

/**
 * Real-valued function
 *
 * Code implementation for any real-valued single-variable function.
 *
 * @param x (double) The argument of the function.
 * @return (double) The value of the function.
 */
double f(double x) { return (1 + exp(-x) * __builtin_sin(4 * x)); }

int main() {
  long double a, b;
  long long n;

  std::cout << "Enter the lower bound of the integral (a): ";
  std::cin >> a;

  std::cout << "Enter the upper bound of the integral (b): ";
  std::cin >> b;

  std::cout << "Enter the number of divisions (n): ";
  std::cin >> n;

  long double h = (b - a) / n, inner_sum = f(a) + f(b);

  for (long long i = 1; i < n; i++) {
    if ((i & 1) != 0)
      inner_sum += 4 * f(a + (i * h));
    else
      inner_sum += 2 * f(a + (i * h));
  }

  std::cout << "Approximate value of the integral: " << std::setprecision(17)
            << (h / 3) * inner_sum << std::endl;

  return 0;
}
