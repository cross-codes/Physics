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

  std::cout << "Enter the lower bound of the integral (a): ";
  std::cin >> a;

  std::cout << "Enter the upper bound of the integral (b): ";
  std::cin >> b;

  std::ofstream data_file("/tmp/trapezoid.dat");
  std::vector<double> arr;

  for (int n = 5; n <= 250; n = n + 5) {
    double h = (b - a) / n, sum = f(a) + f(b);

    for (int i = 1; i < n; i++) {
      sum += 2 * f(a + (i * h));
    }

    arr.push_back((h / 2) * sum);
  }

  double ans = arr[arr.size() - 1];

  for (long unsigned i = 0, n = 5; i < arr.size() - 1 && n <= 250;
       i++, n = n + 5) {
    data_file << n << " " << std::abs(arr[i] - ans) << std::endl;
  }

  system("gnuplot -p plot.gp");

  data_file.close();
  return 0;
}
