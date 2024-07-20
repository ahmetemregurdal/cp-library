#include <algorithm>
#include <cmath>
#include <cstdint>
#include <initializer_list>
#include <numeric>
#include <vector>
namespace primeTest {
typedef uint64_t u64;
typedef __uint128_t u128;
u64 binpower(u64 base, u64 e, u64 mod) {
  u64 result = 1;
  base %= mod;
  while (e) {
    if (e & 1)
      result = (u128)result * base % mod;
    base = (u128)base * base % mod;
    e >>= 1;
  }
  return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
  u64 x = binpower(a, d, n);
  if (x == 1 || x == n - 1)
    return false;
  for (int r = 1; r < s; r++) {
    x = (u128)x * x % n;
    if (x == n - 1)
      return false;
  }
  return true;
};
}; // namespace primeTest
bool is_prime(const unsigned long long &n) {
  if (n < 2)
    return false;

  int r = 0;
  unsigned long long d = n - 1;
  while ((d & 1) == 0) {
    d >>= 1;
    r++;
  }

  for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a)
      return true;
    if (primeTest::check_composite(n, a, d, r))
      return false;
  }
  return true;
}
namespace primeFactorization {
typedef int64_t i64;
typedef __int128_t i128;
typedef int32_t i32;
inline i64 mult(i64 a, i64 b, i64 mod) { return (i128)a * b % mod; }
inline i64 f(i64 x, i64 c, i64 mod) { return (mult(x, x, mod) + c) % mod; }
i64 rho(i64 n, i64 x0 = 2, i64 c = 1) {
  if (n % 2 == 0)
    return 2;
  i64 x = x0;
  i64 y = x0;
  i64 g = 1;
  while (g == 1) {
    x = f(x, c, n);
    y = f(y, c, n);
    y = f(f(y, c, n), c, n);
    g = std::gcd(x > y ? x - y : y - x, n);
  }
  return g;
}
std::vector<i64> factorize(i64 n) {
  std::vector<i64> factors;
  while (!is_prime(n) && n > 1) {
    int64_t factor = primeFactorization::rho(n);
    int i = 2;
    while (factor == n) {
      factor = primeFactorization::rho(n, i, 1);
      i++;
    }
    n /= factor;
    std::vector<i64> partial = factorize(factor);
    factors.insert(factors.end(), partial.begin(), partial.end());
  }
  if (n > 1)
    factors.push_back(n);
  return factors;
}
} // namespace primeFactorization

std::vector<int64_t> prime_factorization(int64_t n) {
  std::vector<int64_t> ans = primeFactorization::factorize(n);
  std::sort(ans.begin(), ans.end());
  return ans;
}
