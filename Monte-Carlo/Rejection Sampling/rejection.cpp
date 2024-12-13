#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

std::random_device rd{};
std::mt19937_64 gen{rd()};

double gen_uniform_random(double a, double b) {
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(gen);
}

double test(double x, int n) { return pow(4 * x * (1 - x), n); }

int32_t main() {
  int cnt = 0;
  for (int i = 0; i < 10; i++) {
    cnt = 0;
    while (true) {
      double u = gen_uniform_random(0, 1);
      double u_input = gen_uniform_random(0, 1);
      if (u <= test(u_input, 3)) {
        std::cout << u << " ";
        std::cout << cnt << "\n";
        break;
      } else
        cnt++;
    }
  }
}
