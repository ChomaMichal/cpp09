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
    if (errno == ERANGE || tmp < 0 || tmp > INT_MAX)
      throw(std::runtime_error("Overflow detected in inout"));
    if (*errcheck != 0) {
      throw(std::runtime_error("Invalid argument"));
    }
    rt.push_back(tmp);
  }
  return (rt);
}

int main(int argc, char **argv) {
  try {
    if (argc == 1) {
      std::cerr << "Give numbers as arguments" << std::endl;
      return 1;
    }
    std::vector<int> vec = process_input(argv);
    // print_c(vec);

    vec = vec_pmerge_me(vec);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
