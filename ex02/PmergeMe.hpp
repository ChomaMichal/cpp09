#pragma once
#include <iostream>
#include <vector>

typedef struct r_pair {
  r_pair *rest_bigger;
  r_pair *rest_smaller;
  int bigger;
  int smaller;
  bool alone;
} r_pair;
std::vector<r_pair *> create_pair(std::vector<r_pair *> &pairs);
std::vector<r_pair *> create_pair(std::vector<int> &pairs);
void vec_pmerge_me(std::vector<int> &vec);

void print_r_pair(r_pair *pair);
