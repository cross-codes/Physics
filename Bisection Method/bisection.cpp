#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>

// Bisection method on f(x)

double f(double x) { return (std::pow(x, 3) - x - 2); }

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
    std::cout << "Condition f(a) < f(b) not satisfied" << std::endl;
    return -1;
  }

  // File to store iterations
  std::ofstream dataFile("/tmp/bisection.dat");

  int n = 0;

  while (n <= N_MAX) {
    double c = (a + b) / 2.0;
    std::cout << "Iteration: " << n << ", Value of a " << a << ", Value of b "
              << b << std::endl;

    dataFile << b - a << " " << n << std::endl;

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

    n++;
  }

  std::cout << "ERROR: Method failed" << std::endl;
  dataFile.close();

  return 0;
}
