#include <bits/stdc++.h>

/**
 * Real-valued function
 *
 * Code implementation for any real-valued single-variable function.
 *
 * @param x (double) The argument of the function.
 * @return (double) The value of the function.
 */
double f(double x) { return (std::pow(x, 1.5) - 13); }

/**
 * Real-valued function derivative
 *
 * Code implementation for the derivative of a real-valued single-variable
 * function
 *
 * @param x (double) The argument of the function.
 * @return (double) The value of the function.
 */
double f_prime(double x) { return (1.5 * sqrt(x)); }

int main() {
  double x0, TOL;

  int N_MAX = 50;

  std::cout << "Enter the value of a best-guess root (x0): ";
  std::cin >> x0;

  std::cout << "Enter the base-10 logarithm of the tolerance (log(TOL)): ";
  std::cin >> TOL;

  TOL = std::pow(10, TOL);

  for (int i = 0; i < N_MAX; i++) {
    double y = f(x0);
    double y_prime = f_prime(x0);

    if (std::abs(y_prime) < 1e-9)
      break;

    double x1 = x0 - (y / y_prime);

    std::cout << "Iteration " << i
              << " : Estimate x1 = " << std::setprecision(17) << x1 << "\n";

    if (std::abs(x1 - x0) <= TOL) {
      std::cout << "Acceptable root found: " << std::setprecision(17) << x1
                << std::endl;
      return 0;
    }

    x0 = x1;
  }

  std::cout << "The method does not converge fast enough";
  return -1;
}
