#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

/**
 * Derivative
 *
 * Code implementation for any real-valued derivative
 *
 * @param t (long double) The first argument of the function.
 * @param y (long double) The second argument of the function.
 * @return (long double) The value of the function.
 */
long double dydx(long double t, long double y) { return (t + y + t * y); }

int32_t main() {
  long double t0, y0, h, t1;

  std::cout << "Enter the initial value (t0): ";
  std::cin >> t0;

  std::cout << "Enter the value of the function at this point (y(t0)): ";
  std::cin >> y0;

  std::cout << "Enter the value of the step size (h): ";
  std::cin >> h;

  std::cout << "Enter the value at which you need to approximate y: ";
  std::cin >> t1;

  while (t0 < t1) {
    y0 += h * dydx(t0, y0);
    t0 += h;
  }

  std::cout << "Approximate solution at x = " << t1 << " is " << y0
            << std::endl;

  return 0;
}
