#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

double pi(double x) { return exp(-x * x / 2) * 1 / sqrt(2 * M_PI); }

double POSITION = 0.1L;
double D = 0.5L;

int32_t main() {
  std::ofstream data_file("/tmp/continuous_markov_chain.dat");
  for (int i = 0; i < 1e6; i++) {
    double rv = gen_uniform_random(-D / 2, D / 2);
    double next_position = POSITION + rv;
    double move_probability = std::min(1.0, pi(next_position) / pi(POSITION));

    double dice = gen_uniform_random(0.0, 1.0);
    if (dice < move_probability) {
      POSITION = next_position;
    }

    data_file << i << " " << POSITION << std::endl;
  }

  data_file.close();

  system("gnuplot -p continuous_markov_chain.gp");

  return 0;
}
