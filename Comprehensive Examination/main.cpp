#pragma float_control(precise, on)

#include <bits/stdc++.h>

// Solution attempt for Q1
// Author: 2022B5A70289P

// Constants
double GAMMA = 0.1;
double OMEGA_0 = 2 * M_PI;

double dy_dt(double t, double y, double z) { return z; }

double dz_dt(double t, double y, double z) {
  return -(OMEGA_0 * OMEGA_0 * y) - (2 * GAMMA * z);
}

int32_t main() {
  std::cout << "---------------\n";
  std::cout << "     PART A\n";
  std::cout << "---------------\n";

  double t = 0.0, y = 1, z = 0;
  double h = 1e-4;
  long N = 0;
  while (t < 3) {
    double k1 = dy_dt(t, y, z);
    double l1 = dz_dt(t, y, z);

    double k2 = dy_dt(t + (h / 2.0), y + (h * k1 / 2), z + (h * l1 / 2));
    double l2 = dz_dt(t + (h / 2.0), y + (h * k1 / 2), z + (h * l1 / 2));

    double k3 = dy_dt(t + (h / 2.0), y + (h * k2 / 2), z + (h * l2 / 2));
    double l3 = dz_dt(t + (h / 2.0), y + (h * k2 / 2), z + (h * l2 / 2));

    double k4 = dy_dt(t + h, y + (h * k3), z + (h * l3));
    double l4 = dz_dt(t + h, y + (h * k3), z + (h * l3));

    y += (h / 6.0) * (k1 + (2 * k2) + (2 * k3) + k4);
    z += (h / 6.0) * (l1 + (2 * l2) + (2 * l3) + l4);
    t += h;
    N++;
  }

  std::cout << "Number of iterations: " << N << "\n";
  std::cout << "Calculated value of y(3): " << y << "\n";
  std::cout << "Calculated value of v(3): " << z << "\n";

  std::cout << "---------------\n";
  std::cout << "     PART B\n";
  std::cout << "---------------\n";

  double reference_value = y;

  // Generate equidistant values
  double h_values[10];
  double jump = (0.3 - 0.03) / 9, start = 0.03;
  for (int i = 0; i < 10; i++) {
    h_values[i] = start;
    start += jump;
  }

  double errors[10];

  for (int i = 0; i < 10; i++) {
    double h = h_values[i];
    t = 0.0;
    y = 1;
    z = 0;
    while (t < 3) {
      double k1 = dy_dt(t, y, z);
      double l1 = dz_dt(t, y, z);

      double k2 = dy_dt(t + (h / 2.0), y + (h * k1 / 2), z + (h * l1 / 2));
      double l2 = dz_dt(t + (h / 2.0), y + (h * k1 / 2), z + (h * l1 / 2));

      double k3 = dy_dt(t + (h / 2.0), y + (h * k2 / 2), z + (h * l2 / 2));
      double l3 = dz_dt(t + (h / 2.0), y + (h * k2 / 2), z + (h * l2 / 2));

      double k4 = dy_dt(t + h, y + (h * k3), z + (h * l3));
      double l4 = dz_dt(t + h, y + (h * k3), z + (h * l3));

      y += (h / 6.0) * (k1 + (2 * k2) + (2 * k3) + k4);
      z += (h / 6.0) * (l1 + (2 * l2) + (2 * l3) + l4);
      t += h;
    }

    errors[i] = std::abs(y - reference_value);
  }

  double log_errors[10];

  for (int i = 0; i < 10; i++)
    log_errors[i] = log(errors[i]) / log(10); // log here is actually base e

  // Opening a file to write log_10(h) vs log_10(error) on
  std::ofstream log_plot("/tmp/log_plot.dat");
  std::cout << "log_10(error) log_10(h)\n\n";

  for (int i = 0; i < 10; i++) {
    double h = h_values[i];
    log_plot << log_errors[i] << " " << log(h) / log(10) << std::endl;
    std::cout << log_errors[i] << " " << log(h) / log(10) << "\n";
  }

  log_plot.close();

  // Execute gnuplot -p log_plot.gp on the terminal to produce the graph

  // Slope calculation:
  std::cout << "\nSlope using 2nd and 7th points: "
            << (log(h_values[6]) - log(h_values[1])) /
                   (log_errors[6] - log_errors[1])
            << "\n";

  std::cout << "---------------\n";
  std::cout << "     PART C\n";
  std::cout << "---------------\n";

  std::ofstream y_plot("/tmp/y_plot.dat");
  std::ofstream yz_plot("/tmp/yz_plot.dat");

  t = 0.0, y = 1, z = 0;
  h = 0.1;

  while (t < 3) {
    double k1 = dy_dt(t, y, z);
    double l1 = dz_dt(t, y, z);

    double k2 = dy_dt(t + (h / 2.0), y + (h * k1 / 2), z + (h * l1 / 2));
    double l2 = dz_dt(t + (h / 2.0), y + (h * k1 / 2), z + (h * l1 / 2));

    double k3 = dy_dt(t + (h / 2.0), y + (h * k2 / 2), z + (h * l2 / 2));
    double l3 = dz_dt(t + (h / 2.0), y + (h * k2 / 2), z + (h * l2 / 2));

    double k4 = dy_dt(t + h, y + (h * k3), z + (h * l3));
    double l4 = dz_dt(t + h, y + (h * k3), z + (h * l3));

    y += (h / 6.0) * (k1 + (2 * k2) + (2 * k3) + k4);
    z += (h / 6.0) * (l1 + (2 * l2) + (2 * l3) + l4);
    t += h;

    std::cout << "t: " << t << "\n";
    std::cout << "y: " << y << "\n";
    std::cout << "z: " << z << "\n\n";

    y_plot << t << " " << y << std::endl;
    yz_plot << z << " " << y << std::endl;
  }

  return 0;
}
