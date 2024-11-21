#include <fstream>
#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

void generate_random_walk(std::ofstream &file) {
  long long x0 = 0LL;
  for (long long i = 0; i < 1e3; i++) {
    file << i << " " << x0 << std::endl;
    long double rv = gen_uniform_random(0, 1);
    if (rv > 0.5L) {
      x0 += 1LL;
    } else {
      x0 -= 1LL;
    }
  }
}

int32_t main() {
  for (int i = 0; i < 500; i++) {
    std::ofstream data_file("/tmp/rv_1D_" + std::to_string(i) + ".dat");
    generate_random_walk(data_file);
    data_file.close();
  }

  system("gnuplot -p random_walk_distribution.gp");
}
