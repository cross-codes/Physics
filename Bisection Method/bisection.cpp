#include <bits/stdc++.h>

/**
 * Real-valued function
 *
 * Code implementation for any real-valued single-variable function.
 *
 * @param x (double) The argument of the function.
 * @return (double) The value of the function.
 */
double f(double x) { return (std::pow(x, 2) - 3); }

int main() {
  double a, b, TOL;

  int N_MAX = 50;

  std::cout << "Enter the value of the first limit (a): ";
  std::cin >> a;
  std::cout << "Enter the value of the first limit (b): ";
  std::cin >> b;

  std::cout << "Enter the base-10 logarithm of the tolerance (log(TOL)): ";
  std::cin >> TOL;

  TOL = std::pow(10, TOL);

  // Pre-checks
  if (a >= b) {
    std::cout << "Condition a < b not satisfied. Exiting" << std::endl;
    return -1;
  }

  if ((f(a) * f(b)) >= 0) {
    std::cout << "Condition f(a) * f(b) < 0 not satisfied. Exiting" << std::endl;
    return -1;
  }

  // File to store iterations
  std::ofstream dataFile("/tmp/bisection.dat");

  int i = 0;
  std::vector<double> arr;

  while (i <= N_MAX) {
    double c = (a + b) / 2.0;
    std::cout << "Iteration: " << i << ", Value of a " << a << ", Value of b "
              << b << std::endl;

    arr.push_back(std::abs(b - a));

    if (arr.size() > 1) {
      dataFile << i << " " << arr[i] / arr[i - 1] << std::endl;
    }

    if (f(c) == 0 || (b - a) / 2.0 < TOL) {
      std::cout << "Approximate root found: " << c << std::endl;
      dataFile.close();
      system("gnuplot -p plot.gp");
      return 0;
    }

    if (f(a) * f(c) > 0)
      a = c;
    else
      b = c;

    i++;
  }

  std::cout << "ERROR: Method failed" << std::endl;
  dataFile.close();

  return -1;
}
