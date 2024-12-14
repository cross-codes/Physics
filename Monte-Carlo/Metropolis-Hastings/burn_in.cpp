#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

double gen_normal_random(double mean, double stdev) {
  std::normal_distribution<double> distribution(mean, stdev);
  return distribution(gen);
}

double target(double x) { return exp(-x * x / 2) * 1 / sqrt(2 * M_PI); }

double autocorrelation(const std::vector<double> &markov_chain, int tau) {
  int n = markov_chain.size();

  double mean =
      std::accumulate(markov_chain.begin(), markov_chain.end(), 0.0) / n;

  double var = 0.0;
  for (double value : markov_chain) {
    var += std::pow(value - mean, 2);
  }
  var /= n;

  std::vector<double> ch1(n - tau);
  std::vector<double> ch2(n - tau);

  // Calculate ch1 and ch2
  for (int i = 0; i < n - tau; ++i) {
    ch1[i] = markov_chain[i] - mean;
    ch2[i] = markov_chain[i + tau] - mean;
  }

  double product = 0.0;
  for (int i = 0; i < n - tau; ++i) {
    product += ch1[i] * ch2[i];
  }

  return product / var / (n - tau);
}

int32_t main() {
  // Histogram verification

  std::ofstream data_file("/tmp/burn_in.dat");
  std::map<long, long, std::greater<long>> bins;
  std::vector<double> markov_chain;

  markov_chain.push_back(3.0);

  for (int i = 1; i < 1e6; i++) {

    double current_x = markov_chain[i - 1];
    double proposed_x = current_x + gen_uniform_random(-0.5, 0.5);
    double acceptance_prob =
        std::min(1.0, target(proposed_x) / target(current_x));

    double u = gen_uniform_random(0, 1);
    if (u < acceptance_prob)
      markov_chain.push_back(proposed_x);
    else
      markov_chain.push_back(current_x);
  }

  for (double val : markov_chain)
    bins[(int)floor(val * 100)]++;

  std::pair<const long, long> pair = *bins.begin();
  std::pair<const long, long> end_pair = *bins.rbegin();
  for (long i = end_pair.first; i <= pair.first; i++) {
    data_file << i << " " << bins[i] << "\n";
  }

  data_file.close();

  // Burn in - Plot expected x values over number of iterations
  std::ofstream burn_in_file("/tmp/burn_in_x.dat");
  double current_sum = 0;
  for (long unsigned int i = 0; i < markov_chain.size(); i++) {
    current_sum += markov_chain[i];
    burn_in_file << i << " " << 1.0 / (i + 1) * current_sum << "\n";
  }

  return 0;
}
