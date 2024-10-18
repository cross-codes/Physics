#include <bits/stdc++.h>

/**
 * Derivative
 * Here dydt = dy/dt = f(t, y) and
 * y(t0) = y0
 */
long double dydt(long double t, long double y) {
  return (t + std::pow(y, 2));
}

int main() {

  long double y0, t0, h, t_final;

  std::cout << "Enter the initial value (t0): ";
  std::cin >> t0;

  std::cout << "Enter the value of the function at this point (y0 = y(t0)): ";
  std::cin >> y0;

  std::cout << "Enter the value of the step size (h): ";
  std::cin >> h;

  std::cout << "Enter the value at which you need to approximate y (t_final): ";
  std::cin >> t_final;

  std::ofstream data_file("/tmp/rk4.dat");

  data_file << t0 << " " << y0 << std::endl;

  while (t0 < t_final) {
    long double k1 = dydt(t0, y0);
    long double k2 = dydt(t0 + 0.5 * h, y0 + h * 0.5 * k1);
    long double k3 = dydt(t0 + 0.5 * h, y0 + h * 0.5 * k2);
    long double k4 = dydt(t0 + h, y0 + h * k3);

    std::cout << k1 << "\n";
    std::cout << k2 << "\n";
    std::cout << k3 << "\n";
    std::cout << k4 << "\n";

    t0 += h;
    y0 += (h / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
    data_file << t0 << " " << y0 << std::endl;
  }

  data_file.close();

  std::cout << "The approximate value of y at x = " << t_final << " is " << y0
            << std::endl;

  system("gnuplot -p plot.gp");

  return 0;
}
