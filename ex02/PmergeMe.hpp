#pragma once
#include <iostream>
#include <list>
#include <vector>

typedef struct r_pair {
  r_pair *rest_bigger;
  r_pair *rest_smaller;
  int bigger;
  int smaller;
  bool alone;
} r_pair;

std::vector<r_pair *> create_pair(std::vector<r_pair> &pairs);
std::vector<r_pair *> create_pair(std::vector<int> &pairs);
std::vector<int> vec_pmerge_me(std::vector<int> &vec);
std::vector<int> list_pmerge_me(std::vector<int> &vec);
std::list<int> list_pmerge_me(std::list<int> &vec);
std::list<r_pair *> create_pair(std::list<int> &vec);

std::list<r_pair *> create_pair(std::list<r_pair *> &pairs);

void print_r_pair(r_pair *pair);

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

