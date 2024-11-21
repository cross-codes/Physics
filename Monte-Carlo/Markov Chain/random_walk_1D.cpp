#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

int32_t main() {
  // Initial position: X0 = 0
  long long x0 = 0LL;

  // Generate XN = XN-1 + wN
  std::ofstream data_file("/tmp/random_walk_1D.dat");
  for (long long i = 0; i <= 1e3; i++) {
    data_file << i << " " << x0 << std::endl;
    long double rv = gen_uniform_random(0, 1);
    if (rv > 0.5L) {
      x0 += 1LL;
    } else {
      x0 -= 1LL;
    }
  }

  data_file.close();
  system("gnuplot -p random_walk_1D_plot.gp");

  return 0;
}
