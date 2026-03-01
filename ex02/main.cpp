#include "PmergeMe.hpp"
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

std::vector<int> process_input(char **argv) {
  std::vector<int> rt;

  for (size_t i = 1; argv[i]; i++) {
    errno = 0;
    char *errcheck;
    long tmp = std::strtol(argv[i], &errcheck, 10);
    if (errno == ERANGE || tmp < 0 || tmp > INT_MAX) {
      throw(std::runtime_error("Error"));
    }
    if (*errcheck != 0) {
      throw(std::runtime_error("Error"));
    }
    rt.push_back(tmp);
  }
  return (rt);
}

void print_sequence(const std::vector<int> &seq) {
  for (size_t i = 0; i < seq.size(); i++) {
    if (i > 0)
      std::cout << " ";
    std::cout << seq[i];
  }
  std::cout << std::endl;
}

void print_sequence(const std::list<int> &seq) {
  size_t i = 0;
  for (std::list<int>::const_iterator it = seq.begin(); it != seq.end(); ++it) {
    if (i > 0)
      std::cout << " ";
    std::cout << *it;
    i++;
  }
  std::cout << std::endl;
}

int main(int argc, char **argv) {
  try {
    if (argc == 1) {
      std::cerr << "Error" << std::endl;
      return 1;
    }

    std::vector<int> vec = process_input(argv);

    std::cout << "Before: ";
    print_sequence(vec);

    std::list<int> lst;
    for (size_t i = 0; i < vec.size(); i++) {
      lst.push_back(vec[i]);
    }

    clock_t vec_start = clock();
    std::vector<int> sorted_vec = vec_pmerge_me(vec);
    clock_t vec_end = clock();
    double vec_time =
        static_cast<double>(vec_end - vec_start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "After: ";
    print_sequence(sorted_vec);

    clock_t list_start = clock();
    std::list<int> sorted_list = list_pmerge_me(lst);
    clock_t list_end = clock();
    double list_time =
        static_cast<double>(list_end - list_start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of " << sorted_vec.size()
              << " elements with std::vector : " << std::fixed
              << std::setprecision(5) << vec_time << " us" << std::endl;

    std::cout << "Time to process a range of " << sorted_list.size()
              << " elements with std::list : " << std::fixed
              << std::setprecision(5) << list_time << " us" << std::endl;

  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
