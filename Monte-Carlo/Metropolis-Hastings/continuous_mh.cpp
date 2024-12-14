#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

/*
  Distribution: exp(-x) (x >= 0)
  Transition kernel H: N(x, 1)
*/

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

double target(double x) {
  if (x < 0)
    return 0;
  return exp(-x);
}

int32_t main() {
  std::vector<double> markov_chain;
  std::map<long, long, std::greater<long>> bins;

  // Initial value way off the mean
  markov_chain.push_back(3.0);

  for (int i = 1; i < 1e6; i++) {
    double current_x = markov_chain[i - 1];
    double proposed_x =
        current_x + gen_normal_random(0, 1); // Random walk proposal
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

  std::ofstream data_file("/tmp/continuous_mh.dat");

  std::pair<const long, long> pair = *bins.begin();
  for (int i = 0; i <= pair.first; i++) {
    data_file << i << " " << bins[i] << "\n";
  }

  data_file.close();

  return 0;
}
