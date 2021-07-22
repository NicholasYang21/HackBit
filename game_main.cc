#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <random>


int
main() {
  std::vector<long long> test_vec;
  std::list<long long> test_list;
  auto beg = clock();
  for (auto i = 0; i < 1000000; ++i) {
    test_vec.emplace_back(0);
  }
  auto end = clock();
  std::cout << (double)(end - beg) / CLOCKS_PER_SEC << std::endl;
  beg = clock();
  for (auto i = 0; i < 1000000; ++i) {
    test_list.emplace_back(0);
  }
  end = clock();
  std::cout << (double)(end - beg) / CLOCKS_PER_SEC;
  return 0;
}