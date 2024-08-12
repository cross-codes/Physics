#include <bits/stdc++.h>

/**
 * Real-valued function
 *
 * Code implementation for any real-valued single-variable function.
 *
 * @param x (double) The argument of the function.
 * @return (double) The value of the function.
 */
double f(double x) { return exp(x); }

int main() {
  double a, b;
  long long n;

  std::cout << "Enter the lower bound of the integral (a): ";
  std::cin >> a;

  std::cout << "Enter the upper bound of the integral (b): ";
  std::cin >> b;

  std::cout << "Enter the number of divisions (n): ";
  std::cin >> n;

  double h = (b - a) / n, sum = f(a) + f(b);

  for (int i = 1; i < n; i++) {
    sum += 2 * f(a + (i * h));
  }

  std::cout << "Approximate value of integral " << std::setprecision(17)
            << (h / 2) * sum << std::endl;

  return 0;
}
