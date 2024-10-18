#include <bits/stdc++.h>

/**
 * Derivative
 *
 */
long double dydt(long double t, long double y, long double z) { return z; }

/**
 * Derivative
 *
 */
long double dzdt(long double t, long double y, long double z) {
  return 6 * y - z;
}

int main() {
  long double t0, y0, z0, h, t_final;

  std::cout << "Enter the initial value (t0): ";
  std::cin >> t0;

  std::cout << "Enter the value of the f at this point (y0 = y(t0)): ";
  std::cin >> y0;

  std::cout << "Enter the value of the g at this point (z0 = z(t0)): ";
  std::cin >> z0;

  std::cout << "Enter the value of the step size (h): ";
  std::cin >> h;

  std::cout << "Enter the value at which you need to approximate t: ";
  std::cin >> t_final;

  while (t0 < t_final) {
    long double k1 = dydt(t0, y0, z0);
    long double l1 = dzdt(t0, y0, z0);

    long double k2 = dydt(t0 + 0.5 * h, y0 + 0.5 * h * k1, z0 + 0.5 * h * l1);
    long double l2 = dzdt(t0 + 0.5 * h, y0 + 0.5 * h * k1, z0 + 0.5 * h * l1);

    long double k3 = dydt(t0 + 0.5 * h, y0 + 0.5 * h * k2, z0 + 0.5 * h * l2);
    long double l3 = dzdt(t0 + 0.5 * h, y0 + 0.5 * h * k2, z0 + 0.5 * h * l2);

    long double k4 = dydt(t0 + h, y0 + h * k3, z0 + h * l3);
    long double l4 = dzdt(t0 + h, y0 + h * k3, z0 + h * l3);

    y0 += (h / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
    z0 += (h / 6.0) * (l1 + 2 * l2 + 2 * l3 + l4);
    t0 += h;
  }

  std::cout << "The approximate value of y at t = " << t_final << " is " << y0
            << std::endl;
}
