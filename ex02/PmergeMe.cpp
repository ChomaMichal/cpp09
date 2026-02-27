#include "PmergeMe.hpp"
#include <vector>

std::vector<r_pair> create_pair(std::vector<int> &vec) {
  std::vector<int>::iterator iter = vec.begin();
  std::vector<r_pair> rt;
  while (true) {
    std::vector<int>::iterator el1 = iter;
    iter++;
    if (iter == vec.end()) {
      r_pair single;
      single.bigger = *el1;
      single.rest_bigger = NULL;
      single.rest_smaller = NULL;
      single.alone = true;
      rt.push_back(single);
      break;
    }
    std::vector<int>::iterator el2 = iter;
    if (*el1 > *el2) {
      r_pair pair;
      pair.bigger = *el1;
      pair.rest_bigger = NULL;
      pair.smaller = *el2;
      pair.rest_smaller = NULL;
      pair.alone = false;
      rt.push_back(pair);
    } else {
      r_pair pair;
      pair.bigger = *el2;
      pair.rest_bigger = NULL;
      pair.smaller = *el1;
      pair.rest_smaller = NULL;
      pair.alone = false;
      rt.push_back(pair);
    }
    iter++;
    if (iter == vec.end())
      break;
  }
  for (int i = 0; i != rt.size(); i++) {
    print_r_pair(&rt[i]);
    std::cout << " in first iteration\n";
  }
  return (rt);
}

std::vector<r_pair> create_pair(std::vector<r_pair> &pairs) {
  std::vector<r_pair>::iterator iter = pairs.begin();
  std::vector<r_pair> rt;
  while (true) {
    std::vector<r_pair>::iterator el1 = iter;
    iter++;
    if (iter == pairs.end()) {
      r_pair single;
      single.bigger = el1->bigger;
      single.rest_bigger = &*el1;
      single.alone = true;
      break;
    }
    std::vector<r_pair>::iterator el2 = iter;
    if (el1->bigger > el2->bigger) {
      r_pair pair;
      pair.bigger = el1->bigger;
      pair.rest_bigger = &*el1;
      pair.smaller = el2->smaller;
      pair.rest_smaller = &*el2;
      pair.alone = false;
      rt.push_back(pair);
    } else {
      r_pair pair;
      pair.bigger = el2->bigger;
      pair.rest_bigger = &*el2;
      pair.smaller = el1->smaller;
      pair.rest_smaller = &*el1;
      pair.alone = false;
      rt.push_back(pair);
    }
    iter++;
    if (iter == pairs.end())
      break;
  }
  for (int i = 0; i != rt.size(); i++) {
    print_r_pair(&rt[i]);
    std::cout << " in rec iteration\n";
  }
  return (rt);
}

void print_r_pair(r_pair *pair) {
  if (pair == NULL)
    return;
  if (pair->alone == true) {
    std::cout << "[" << pair->bigger << "]";
    return;
  }

  if (pair->rest_bigger == NULL) {
    std::cout << "[" << pair->bigger << ", " << pair->smaller << "]";
    return;
  }
  std::cout << "[";
  print_r_pair(pair->rest_bigger);
  std::cout << ", ";
  print_r_pair(pair->rest_smaller);
  std::cout << "]";
}

void vec_pmerge_me(std::vector<int> &vec) {
  auto tmp = create_pair(vec);
  std::vector<std::vector<r_pair>> fuckof;
  std::cout << '\n';
  while (tmp.size() != 1) {
    fuckof.push_back(tmp);
    tmp = create_pair(tmp);
    std::cout << '\n';
    std::cout << '\n';
  }
  print_r_pair(&tmp[0]);
}
