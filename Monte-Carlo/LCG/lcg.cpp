#pragma GCC target("avx2,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>

int32_t main() {
  long long x;
  int a, c, m;
  std::cout << "Enter the value of the multiplier (a): ";
  std::cin >> a;

  std::cout << "Enter the value of the increment (c): ";
  std::cin >> c;

  std::cout << "Enter the value of the modulus (m): ";
  std::cin >> m;

  std::cout << "Enter the seed (x0): ";
  std::cin >> x;

  for (int i = 1; i <= 15; i++) {
    x = (a * x + c) % m;
    std::cout << "Random number #" << i << ": " << x << "\n";
  }

  return 0;
}
