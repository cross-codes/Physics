#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

double neutrino_distribution(double x) { return 12 * (x * x) * (1 - x); }

/**
 * This is misleading, because it is rather E' / E_max.
 * I realize this isn't E' / E'_max, but the net effect is a constant
 * that the distribution is "scaled" by, and thus should not affect the shape.
 * My plotting device will mark an 'E_max' next to every x division (if I know
 * how to do that)
 */
double prime_ratio(double x, double theta, double beta) {
  double gamma = 1 / sqrt(1 - (beta * beta));
  return gamma * x * (1 + (beta * cos(theta)));
}

// https://math.stackexchange.com/questions/2057903/mean-and-mode-of-a-beta-random-variable
const double M = neutrino_distribution(2.0 / 3.0);

void gen_data(double beta, std::string filename) {

  // Look at 'approach.txt' to see what this is all about
  // It isn't nearly as easy to plot a histogram as it is in python, or at least
  // I don't know how to do it otherwise
  std::map<long, long, std::greater<long>> bins;

  std::ofstream data_file(filename);
  for (int i = 0; i < 1e6; i++) {
    // Rejection sampling, proposal is ~(0, 1);
    double random_x;
    while (true) {
      random_x = gen_uniform_random(0, 1);
      double test = gen_uniform_random(0, 1);
      if (test <= neutrino_distribution(random_x) / M)
        break;
    }
    /**
     * The problem states that we must pick points off of a sphere.
     * An obvious way to do this, is to generate ~(0, 1) numbers for x, y, z
     * Normalize, and then use the direction ratios to get an angle.
     * I do not see the point in doing this, because an alternative way is to
     * sample θ and then Φ to use spherical coordinates with r = 1, but
     * you'd be sampling θ uniformly as ~(0, 2π).
     * Since all angles can be randomly generated, might as well use
     * θ = ~(0, 2π)
     */
    double random_theta = gen_uniform_random(0, 2 * M_PI);
    double x_prime = prime_ratio(random_x, random_theta, beta);
    bins[(int)floor(x_prime * 100)]++;
  }

  std::pair<const long, long> pair = *bins.begin();
  for (int i = 0; i <= pair.first; i++) {
    data_file << i << " " << bins[i] / 1e6 << "\n";
  }

  data_file.close();
}

int32_t main() {
  gen_data(0, "/tmp/neutrino_0.dat");
  gen_data(0.01, "/tmp/neutrino_1.dat");
  gen_data(0.1, "/tmp/neutrino_2.dat");
  gen_data(0.9, "/tmp/neutrino_3.dat");
  gen_data(0.99, "/tmp/neutrino_4.dat");
  // To plot, run the gnuplot commands in a terminal
  return 0;
}
