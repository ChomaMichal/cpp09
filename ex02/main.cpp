#include "PmergeMe.hpp"
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<int> process_input(char **argv) {
  std::vector<int> rt;

  for (size_t i = 1; argv[i]; i++) {
    errno = 0;
    char *errcheck;
    long tmp = std::strtol(argv[i], &errcheck, 10);
    if (errno == ERANGE || tmp < INT_MIN || tmp > INT_MAX)
      throw(std::runtime_error("Overflow detected in inout"));
    if (*errcheck != 0) {
      throw(std::runtime_error("Invalid argument"));
    }
    rt.push_back(tmp);
  }
  return (rt);
}

template <typename T>

void print_c(T &val) {
  std::cout << "[";
  typename T::iterator iter = val.begin();
  if (iter == val.end())
    return;
  while (true) {
    std::cout << *iter;
    iter++;
    if (iter == val.end())
      break;
    std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

int main(int argc, char **argv) {
  try {
    std::vector<int> vec = process_input(argv);
    // print_c(vec);

    vec_pmerge_me(vec);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
