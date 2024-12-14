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

double gaussian(double x, double mean, double stdev) {
  return 1.0 / (stdev * sqrt(2 * M_PI)) *
         exp(-pow(x - mean, 2) / (2 * stdev * stdev));
}

double likelihood(double m, double x_values[], double y_values[], int length) {
  double product = 1.0;
  for (int i = 0; i < length; i++)
    product *= gaussian(y_values[i], m * x_values[i], 1);
  return product;
}

double log_likelihood(double m, double x_values[], double y_values[],
                      int length) {
  double sum = 0.0;
  for (int i = 0; i < length; i++)
    sum += log(gaussian(y_values[i], m * x_values[i], 2));
  return sum;
}

double prior_trust(double m, double value, double trust) {
  return exp(-trust * (m - value) * (m - value));
}

double prior_distrust(double m, double value) {
  return (m - value) * (m - value);
}

double logposterior(double m, double x_values[], double y_values[],
                    int length) {
  double log_lik = log_likelihood(m, x_values, y_values, length);
  double log_pri = log(prior_trust(m, 2, 1));
  return log_lik + log_pri;
}

int32_t main() {
  // (1) Generating perturbed x points

  // noisy.gp
  std::ofstream noisy("/tmp/noisy.dat");
  std::ofstream clean("/tmp/clean.dat");

  // Generate 11 evenly spaces values between 0.5 and 10.5
  // 0.5 + 10x = 10.5 -> x = 1
  // Perturb each value with a random number generated from -1 to 1

  double x_points[11];
  double start = 0.5;
  for (int i = 0; i < 11; i++) {
    x_points[i] = start + gen_uniform_random(-1, 1);
    start++;
  }

  // (2) Generating fake_data corresponding to y points
  // y = 3x + N(0, 3);

  double y_values[11];
  for (int i = 0; i < 11; i++) {
    y_values[i] = x_points[i] * 3 + gen_normal_random(0, 3);
  }

  start = 0.5;
  for (int i = 0; i < 11; i++) {
    noisy << x_points[i] << " " << y_values[i] << "\n";
  }

  for (int i = 0; i < 16; i++) {
    clean << start << " " << 3 * start << "\n";
    start += 0.5;
  }

  noisy.close();
  clean.close();

  // (3) Maximum likelihood estimation
  // Defined functions: gaussian(), likelihood(), log_likelihood()
  // Generate evenly spaced m-values
  // 0 + 999x = 5 -> x = 5 / 999;

  double m_values[999];
  start = 0;
  for (int i = 0; i < 999; i++) {
    m_values[i] = start;
    start += 5.0 / 999;
  }

  // log.gp
  std::ofstream log_likelihood_values("/tmp/log.dat");
  // (4) For each m, calculate log likelihood
  double log_values[999];
  for (int i = 0; i < 999; i++)
    log_values[i] = log_likelihood(m_values[i], x_points, y_values, 11);

  double max_log_value = 0.0;

  // (5) Plot the m-values versus the quantity below
  for (int i = 0; i < 999; i++) {
    if (log_values[i] > max_log_value)
      max_log_value = log_values[i];
  }

  for (int i = 0; i < 999; i++)
    log_likelihood_values << m_values[i] << " "
                          << -2 * (log_values[i] - max_log_value) << "\n";

  log_likelihood_values.close();

  // (6) MAP estimates based on Baye's theorem (Maximum A Posteriori estimate)
  // Defined functions prior_trust(), prior_distrust(), logposterior()
  // Some mistakes somewhere

  double logpost_arr[999];

  for (int i = 0; i < 999; i++) {
    logpost_arr[i] = logposterior(m_values[i], x_points, y_values, 11);
  }

  double logpost_max = -100;
  for (double val : logpost_arr) {
    if (val > logpost_max)
      logpost_max = val;
  }

  std::cout << logpost_max << "\n";

  // (7) The last step was using MH with a target of likelihood(x) *
  // prior_trust(x, 2, 10);

  return 0;
}
