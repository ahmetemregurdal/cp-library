#include "../src/primefactorization.cpp"
#include <bits/stdc++.h>
int main() {
  std::vector<int64_t> tests = {1,         2, 3, 4, 6, 10, 999381247093216751,
                                4295098369};
  std::vector<std::vector<int64_t>> answers{{},
                                            {2},
                                            {3},
                                            {2, 2},
                                            {2, 3},
                                            {2, 5},
                                            {999665081, 999716071},
                                            {65537, 65537}};
  for (int i = 0; i < tests.size(); i++) {
    auto result = prime_factorization(tests[i]);
    if (result != answers[i]) {
      std::cerr << "Test failed: " << tests[i] << "\nexpected:";
      std::copy(answers[i].begin(), answers[i].end(),
                std::ostream_iterator<int64_t>(std::cerr, " "));
      std::cerr << "\nactual:";
      std::copy(result.begin(), result.end(),
                std::ostream_iterator<int64_t>(std::cerr, " "));
      std::cerr << std::endl;
      return 1;
    }
    std::cout << "Test passed: " << tests[i] << std::endl;
  }
}
