#include <cstdlib>
#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

static const int iterations = 100000;

struct SamplePoint {
  double value;
  double stdDev;
};

struct Result {
  SamplePoint monteCarlo;
  SamplePoint rejectionSampling1;
  SamplePoint rejectionSampling2;
  SamplePoint rejectionSampling3;
  SamplePoint roulette1;
  SamplePoint roulette2;
};

double balance(double A, double B, double t) { return A * (1.0 - t) + B * t; }

double f(long double x) { return pow(x, 2); }

double mc_y_avg = 0.0;
double mc_y_square_avg = 0.0;

double rjt1_y_avg = 0.0;
double rjt1_y_square_avg = 0.0;
int rjt_1_sample_count = 0;

double rjt2_y_avg = 0.0;
double rjt2_y_square_avg = 0.0;
int rjt_2_sample_count = 0;

double rjt3_y_avg = 0.0;
double rjt3_y_square_avg = 0.0;
int rjt_3_sample_count = 0;

double roulette1_y_avg = 0.0;
double roulette1_y_square_avg = 0.0;
int roulette_1_sample_count = 0;

double roulette2_y_avg = 0.0;
double roulette2_y_square_avg = 0.0;
int roulette_2_sample_count = 0;

double value = 0.33333;

int32_t main() {

  std::vector<Result> results(iterations);

  for (int index = 1; index <= iterations; ++index) {
    /**
     * Regular Monte-Carlo
     *
     * Calculate the value of f at a random value, add them up
     */
    {
      double x = gen_uniform_random(0, 1);
      double y = f(x);

      mc_y_avg = balance(mc_y_avg, y, 1.0 / double(index));
      mc_y_square_avg = balance(mc_y_square_avg, y * y, 1.0 / double(index));

      results[index - 1].monteCarlo.value = mc_y_avg;
      results[index - 1].monteCarlo.stdDev =
          sqrt(std::abs(mc_y_square_avg) - (mc_y_avg * mc_y_avg));
    }
    /**
     * Rejection sampling - 1
     *
     * The sampling PDF is y = 2x
     */
    {
      double x;
      do {
        x = gen_uniform_random(0, 1);
        rjt_1_sample_count++;
      } while (gen_uniform_random(0, 1) > x);

      double pdf = 2.0 * x;
      double y = f(x) / pdf;

      rjt1_y_avg = balance(rjt1_y_avg, y, 1.0 / double(index));
      rjt1_y_square_avg =
          balance(rjt1_y_square_avg, y * y, 1.0 / double(index));

      results[index - 1].rejectionSampling1.value = rjt1_y_avg;
      results[index - 1].rejectionSampling1.stdDev =
          sqrt(std::abs(rjt1_y_square_avg) - (rjt1_y_avg * rjt1_y_avg));
    }

    /**
     * Rejection sampling - 2
     *
     * The sampling PDF is y = 2(1 - x)
     */
    {
      double x;
      do {
        x = gen_uniform_random(0, 1);
        rjt_2_sample_count++;
      } while (gen_uniform_random(0, 1) > (1 - x));

      double pdf = 2.0 * (1.0 - x);
      double y = f(x) / pdf;

      rjt2_y_avg = balance(rjt2_y_avg, y, 1.0 / double(index));
      rjt2_y_square_avg =
          balance(rjt2_y_square_avg, y * y, 1.0 / double(index));

      results[index - 1].rejectionSampling2.value = rjt2_y_avg;
      results[index - 1].rejectionSampling2.stdDev =
          sqrt(std::abs(rjt2_y_square_avg) - (rjt2_y_avg * rjt2_y_avg));
    }

    /**
     * Rejection sampling - 3
     *
     * The sampling PDF is y = 3(1-x)²
     */
    {
      double x;
      do {
        x = gen_uniform_random(0, 1);
        rjt_3_sample_count++;
      } while (gen_uniform_random(0, 1) > (1 - x) * (1 - x));

      double pdf = 3.0 * (1.0 - x) * (1.0 - x);
      double y = f(x) / pdf;

      rjt3_y_avg = balance(rjt3_y_avg, y, 1.0 / double(index));
      rjt3_y_square_avg =
          balance(rjt3_y_square_avg, y * y, 1.0 / double(index));

      results[index - 1].rejectionSampling3.value = rjt3_y_avg;
      results[index - 1].rejectionSampling3.stdDev =
          sqrt(std::abs(rjt3_y_square_avg) - (rjt3_y_avg * rjt3_y_avg));
    }

    /**
     * Russian roulette
     *
     * The constant killing probability is 25%
     */
    {
      double x = gen_uniform_random(0, 1);
      double y = 0.0;

      double p = 0.25;
      if (gen_uniform_random(0, 1) > p) {
        y = f(x) / 0.75;
        roulette_1_sample_count++;
      } else {
        y = 0.0;
      }

      roulette1_y_avg = balance(roulette1_y_avg, y, 1.0 / double(index));
      roulette1_y_square_avg =
          balance(roulette1_y_square_avg, y * y, 1.0 / double(index));

      results[index - 1].roulette1.value = roulette1_y_avg;
      results[index - 1].roulette1.stdDev =
          sqrt(std::abs(roulette1_y_square_avg) -
               (roulette1_y_avg * roulette1_y_avg));
    }

    // Russian Roulette: the probability of killing a sample is 1-x
    // Meaning the probability of keeping a sample is x
    // So, we are rejection sampling the pdf y=x
    /**
     * Russian roulette
     *
     * The killing probability is 1 - x, where x is randomly generated
     * This is equivalent to rejection sampling on y = x
     */
    {
      double x = gen_uniform_random(0, 1);
      double y = 0.0;

      double p = (1.0 - x);
      if (gen_uniform_random(0, 1) > p) {
        y = f(x) / (1.0 - p);
        roulette_2_sample_count++;
      } else {
        y = 0.0;
      }

      roulette2_y_avg = balance(roulette2_y_avg, y, 1.0f / float(index));
      roulette2_y_square_avg =
          balance(roulette2_y_square_avg, y * y, 1.0f / float(index));

      results[index - 1].roulette2.value = roulette2_y_avg;
      results[index - 1].roulette2.stdDev =
          sqrt(std::abs(roulette2_y_square_avg) -
               (roulette2_y_avg * roulette2_y_avg));
    }
  }

  std::cout << "Number of tests: " << iterations << "\n";
  std::cout << "Actual value: 1 / 3 = " << value << "\n";

  std::cout << std::endl;

  std::cout << "Monte-Carlo regular integration\n";
  std::cout << "Value: " << results.rbegin()->monteCarlo.value
            << ", STDDEV: " << results.rbegin()->monteCarlo.stdDev << "\n";

  std::cout << std::endl;

  std::cout << "Rejection sampling: y = 2x\nNumber of attempts: "
            << rjt_1_sample_count << " ("
            << (double)rjt_1_sample_count * 100.0 / iterations << " %)\n";
  std::cout << "Value: " << results.rbegin()->rejectionSampling1.value
            << ", STDDEV: " << results.rbegin()->rejectionSampling1.stdDev
            << "\n";

  std::cout << std::endl;

  std::cout << "Rejection sampling: y = 2(1 - x)\nNumber of attempts: "
            << rjt_2_sample_count << " ("
            << (double)rjt_2_sample_count * 100.0 / iterations << " %)\n";
  std::cout << "Value: " << results.rbegin()->rejectionSampling2.value
            << ", STDDEV: " << results.rbegin()->rejectionSampling2.stdDev
            << "\n";

  std::cout << std::endl;

  std::cout << "Rejection sampling: y = 3(1-x)²\nNumber of attempts: "
            << rjt_3_sample_count << " ("
            << (double)rjt_3_sample_count * 100.0 / iterations << " %)\n";
  std::cout << "Value: " << results.rbegin()->rejectionSampling3.value
            << ", STDDEV: " << results.rbegin()->rejectionSampling3.stdDev
            << "\n";

  std::cout << std::endl;

  std::cout << "Russian roulette with rejection probability 0.25\n";
  std::cout << "Number of samples: " << roulette_1_sample_count << " ("
            << (double)roulette_1_sample_count * 100.0 / iterations << " %)\n";
  std::cout << "Value: " << results.rbegin()->roulette1.value
            << ", STDDEV: " << results.rbegin()->roulette1.stdDev << "\n";

  std::cout << std::endl;

  std::cout << "Russian roulette with rejection probability 1 - x\n";
  std::cout << "Number of samples: " << roulette_2_sample_count << " ("
            << (double)roulette_2_sample_count * 100.0 / iterations << " %)\n";
  std::cout << "Value: " << results.rbegin()->roulette2.value
            << ", STDDEV: " << results.rbegin()->roulette2.stdDev << "\n";

  std::cout << std::endl;

  // Graph plotting
  std::ofstream monte_carlo("/tmp/project_monte_carlo.dat");
  std::ofstream monte_carlo_diff("/tmp/project_monte_carlo_diff.dat");

  std::ofstream reject_1("/tmp/project_reject_1.dat");
  std::ofstream reject_1_diff("/tmp/project_reject_1_diff.dat");

  std::ofstream reject_2("/tmp/project_reject_2.dat");
  std::ofstream reject_2_diff("/tmp/project_reject_2_diff.dat");

  std::ofstream reject_3("/tmp/project_reject_3.dat");
  std::ofstream reject_3_diff("/tmp/project_reject_3_diff.dat");

  std::ofstream russian_1("/tmp/project_russian_1.dat");
  std::ofstream russian_1_diff("/tmp/project_russian_1_diff.dat");

  std::ofstream russian_2("/tmp/project_russian_2.dat");
  std::ofstream russian_2_diff("/tmp/project_russian_2_diff.dat");

  for (long unsigned int i = 0; i < results.size(); i++) {
    monte_carlo << i << " " << results[i].monteCarlo.stdDev << "\n";
    monte_carlo_diff << i << " "
                     << std::abs(results[i].monteCarlo.value - value) << "\n";

    reject_1 << i << " " << results[i].rejectionSampling1.stdDev << "\n";
    reject_1_diff << i << " "
                  << std::abs(results[i].rejectionSampling1.value - value)
                  << "\n";

    reject_2 << i << " " << results[i].rejectionSampling2.stdDev << "\n";
    reject_2_diff << i << " "
                  << std::abs(results[i].rejectionSampling2.value - value)
                  << "\n";

    reject_3 << i << " " << results[i].rejectionSampling3.stdDev << "\n";
    reject_3_diff << i << " "
                  << std::abs(results[i].rejectionSampling3.value - value)
                  << "\n";

    russian_1 << i << " " << results[i].roulette1.stdDev << "\n";
    russian_1_diff << i << " " << std::abs(results[i].roulette1.value - value)
                   << "\n";
    russian_2 << i << " " << results[i].roulette2.stdDev << "\n";
    russian_2_diff << i << " " << std::abs(results[i].roulette2.value - value)
                   << "\n";
  }

  monte_carlo.close();
  monte_carlo_diff.close();

  reject_1.close();
  reject_1_diff.close();

  reject_2.close();
  reject_2_diff.close();

  reject_3.close();
  reject_3_diff.close();

  russian_1.close();
  russian_1_diff.close();

  russian_2.close();
  russian_2_diff.close();

  system("gnuplot -p plot_variance.gp");
  system("gnuplot -p plot_diff.gp");

  return 0;
}
