#include "PmergeMe.hpp"
#include <algorithm>
#include <list>
#include <vector>

ulong nex_jac_number(ulong &curent, ulong &prev) {
  if (curent == 0) {
    curent = 1;
    prev = 0;
    return 1;
  }
  if (curent == 1) {
    curent = 3;
    prev = 1;
    return 3;
  }
  ulong pair = curent;
  curent = curent + 2 * prev;
  prev = pair;
  return (curent);
}

bool int_cmp(int i, int j) {
#ifdef DEBUG
  static long hehe;
  hehe++;
  std::cout << "This amont of comperesons were made: " << hehe << std::endl;
#endif
  return (i < j);
}

bool int_addr_cmp(int *i, int *j) { return int_cmp(*i, *j); }

std::list<r_pair *> create_pair(std::list<int> &vec) {
  std::list<int>::iterator iter = vec.begin();
  std::list<r_pair *> rt;
  while (true) {
    std::list<int>::iterator el1 = iter;
    iter++;
    if (iter == vec.end()) {
      r_pair *single = new r_pair();
      single->bigger = (*el1);
      single->rest_bigger = NULL;
      single->rest_smaller = NULL;
      single->alone = true;
      rt.push_back(single);
      break;
    }
    std::list<int>::iterator el2 = iter;
    if (int_cmp(*el1, *el2)) {
      r_pair *pair = new r_pair();
      pair->bigger = (*el1);
      pair->rest_bigger = NULL;
      pair->smaller = (*el2);
      pair->rest_smaller = NULL;
      pair->alone = false;
      rt.push_back(pair);
    } else {
      r_pair *pair = new r_pair();
      pair->bigger = (*el2);
      pair->rest_bigger = NULL;
      pair->smaller = (*el1);
      pair->rest_smaller = NULL;
      pair->alone = false;
      rt.push_back(pair);
    }
    iter++;
    if (iter == vec.end())
      break;
  }
  return (rt);
}

std::list<r_pair *> create_pair(std::list<r_pair *> &pairs) {
  std::list<r_pair *>::iterator iter = pairs.begin();
  std::list<r_pair *> rt;
  while (true) {
    std::list<r_pair *>::iterator el1 = iter;
    iter++;
    if (iter == pairs.end()) {
      r_pair *single = new r_pair();
      single->bigger = (*el1)->bigger;
      single->rest_bigger = &*(*el1);
      single->alone = true;
      rt.push_back(single);
      break;
    }
    std::list<r_pair *>::iterator el2 = iter;
    if (int_cmp((*el1)->bigger, (*el2)->bigger)) {
      r_pair *pair = new r_pair();
      pair->bigger = (*el1)->bigger;
      pair->rest_bigger = &*(*el1);
      pair->smaller = (*el2)->smaller;
      pair->rest_smaller = &*(*el2);
      pair->alone = false;
      rt.push_back(pair);
    } else {
      r_pair *pair = new r_pair();
      pair->bigger = (*el2)->bigger;
      pair->rest_bigger = &*(*el2);
      pair->smaller = (*el1)->smaller;
      pair->rest_smaller = &*(*el1);
      pair->alone = false;
      rt.push_back(pair);
    }
    iter++;
    if (iter == pairs.end())
      break;
  }
  return (rt);
}

bool r_pair_comp(r_pair *v1, r_pair *v2) {
  return (int_cmp(v1->bigger, v2->bigger));
}

std::list<r_pair *> insertions(std::list<r_pair *> array, r_pair *left_out) {
  ulong current = 0;
  ulong prev = 0;
  std::list<r_pair *> rt;
  std::list<r_pair *>::iterator pushed = array.begin();
  std::list<r_pair *>::iterator sorted = array.begin();

  while (true) {
    ulong in_pos = nex_jac_number(current, prev);
    if (in_pos == 1) {
      if ((*pushed)->alone == false) {
        rt.push_back((*pushed)->rest_smaller);
      }
      rt.push_back((*pushed)->rest_bigger);
      continue;
    }
    if (current > array.size())
      in_pos = array.size();

    if (prev >= array.size())
      break;
    for (ulong i = prev; i < in_pos; i++) {
      pushed++;
      if (pushed == array.end())
        break;
      rt.push_back((*pushed)->rest_bigger);
    }
    std::list<r_pair *>::iterator unsorted = pushed;
    if (unsorted == array.end())
      unsorted--;
    while (unsorted != sorted) {
      if ((*unsorted)->alone == false) {
        std::list<r_pair *>::iterator pos = std::lower_bound(
            rt.begin(),
            std::find(rt.begin(), rt.end(), (*unsorted)->rest_bigger),
            (*unsorted)->rest_smaller, r_pair_comp);
        rt.insert(pos, (*unsorted)->rest_smaller);
      }
      unsorted--;
    }

    sorted = pushed;
  }

  if (left_out != NULL) {
    std::list<r_pair *>::iterator pos =
        std::lower_bound(rt.begin(), rt.end(), left_out, r_pair_comp);
    rt.insert(pos, left_out->rest_bigger);
    delete left_out;
  }

  for (std::list<r_pair *>::iterator i = array.begin(); i != array.end(); i++) {
    delete *i;
  }
  return (rt);
}

std::list<int> last_insercion(std::list<r_pair *> array, r_pair *left_out) {
  ulong current = 0;
  ulong prev = 0;
  std::list<int *> tmp;
  std::list<r_pair *>::iterator pushed = array.begin();
  std::list<r_pair *>::iterator sorted = array.begin();

  while (true) {
    ulong in_pos = nex_jac_number(current, prev);
    if (in_pos == 1) {
      if ((*pushed)->alone == false) {
        tmp.push_back(&(*pushed)->smaller);
      }
      tmp.push_back(&(*pushed)->bigger);
      continue;
    }
    if (current > array.size())
      in_pos = array.size();

    if (prev >= array.size())
      break;
    for (ulong i = prev; i < in_pos; i++) {
      pushed++;
      if (pushed == array.end())
        break;
      tmp.push_back(&(*pushed)->bigger);
    }
    std::list<r_pair *>::iterator unsorted = pushed;
    if (unsorted == array.end())
      unsorted--;
    while (unsorted != sorted) {
      if ((*unsorted)->alone == false) {
        std::list<int *>::iterator pos = std::lower_bound(
            tmp.begin(),
            std::find(tmp.begin(), tmp.end(), &(*unsorted)->bigger),
            &(*unsorted)->smaller, int_addr_cmp);
        tmp.insert(pos, &(*unsorted)->smaller);
      }
      unsorted--;
    }

    sorted = pushed;
  }

  if (left_out != NULL) {
    std::list<int *>::iterator pos = std::lower_bound(
        tmp.begin(), tmp.end(), &left_out->bigger, int_addr_cmp);
    tmp.insert(pos, &left_out->bigger);
  }

  std::list<int> rt;

  for (std::list<int *>::iterator i = tmp.begin(); i != tmp.end(); i++) {
    rt.push_back(**i);
  }
  for (std::list<r_pair *>::iterator i = array.begin(); i != array.end(); i++) {
    delete *i;
  }
  delete left_out;
  return (rt);
}

std::list<int> list_pmerge_me(std::list<int> &vec) {

  if (vec.size() == 1) {
    return vec;
  }

  std::list<r_pair *> pair = create_pair(vec);
  std::list<r_pair *> left_out;
  if (pair.back()->alone == true) {
    left_out.push_back(pair.back());
    pair.pop_back();
  } else {
    left_out.push_back(NULL);
  }
  while (pair.size() != 1) {
    pair = create_pair(pair);
    if (pair.back()->alone == true) {
      left_out.push_back(pair.back());
      pair.pop_back();
    } else {
      left_out.push_back(NULL);
    }
  }
  while (pair.front()->rest_bigger != NULL) {
    pair = insertions(pair, left_out.back());
    left_out.pop_back();
  }

  std::list<int> rt = last_insercion(pair, left_out.back());
  return (rt);
}

void print_r_pair(r_pair *pair) {
  if (pair == NULL)
    return;
  if (pair->alone == true) {
    if (pair->rest_bigger == NULL) {
      std::cout << "[" << pair->bigger << "]";
      return;
    }
    print_r_pair(pair->rest_bigger);
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
std::vector<int> jac_sequence_n(int n) {
  std::vector<int> rt;
  if (n <= 0)
    return rt;

  rt.push_back(0);
  if (n == 1)
    return rt;

  rt.push_back(1);

  for (int i = 2; i < n; ++i) {
    rt.push_back(rt[i - 1] + 2 * rt[i - 2]);
  }

  return rt;
}

std::vector<r_pair *> create_pair(std::vector<int> &vec) {
  std::vector<int>::iterator iter = vec.begin();
  std::vector<r_pair *> rt;
  while (true) {
    std::vector<int>::iterator el1 = iter;
    iter++;
    if (iter == vec.end()) {
      r_pair *single = new r_pair();
      single->bigger = (*el1);
      single->rest_bigger = NULL;
      single->rest_smaller = NULL;
      single->alone = true;
      rt.push_back(single);
      break;
    }
    std::vector<int>::iterator el2 = iter;
    if ((*el1) > (*el2)) {
      r_pair *pair = new r_pair();
      pair->bigger = (*el1);
      pair->rest_bigger = NULL;
      pair->smaller = (*el2);
      pair->rest_smaller = NULL;
      pair->alone = false;
      rt.push_back(pair);
    } else {
      r_pair *pair = new r_pair();
      pair->bigger = (*el2);
      pair->rest_bigger = NULL;
      pair->smaller = (*el1);
      pair->rest_smaller = NULL;
      pair->alone = false;
      rt.push_back(pair);
    }
    iter++;
    if (iter == vec.end())
      break;
  }
  return (rt);
}

std::vector<r_pair *> create_pair(std::vector<r_pair *> &pairs) {
  std::vector<r_pair *>::iterator iter = pairs.begin();
  std::vector<r_pair *> rt;
  while (true) {
    std::vector<r_pair *>::iterator el1 = iter;
    iter++;
    if (iter == pairs.end()) {
      r_pair *single = new r_pair();
      single->bigger = (*el1)->bigger;
      single->rest_bigger = &*(*el1);
      single->alone = true;
      rt.push_back(single);
      break;
    }
    std::vector<r_pair *>::iterator el2 = iter;
    if ((*el1)->bigger > (*el2)->bigger) {
      r_pair *pair = new r_pair();
      pair->bigger = (*el1)->bigger;
      pair->rest_bigger = &*(*el1);
      pair->smaller = (*el2)->smaller;
      pair->rest_smaller = &*(*el2);
      pair->alone = false;
      rt.push_back(pair);
    } else {
      r_pair *pair = new r_pair();
      pair->bigger = (*el2)->bigger;
      pair->rest_bigger = &*(*el2);
      pair->smaller = (*el1)->smaller;
      pair->rest_smaller = &*(*el1);
      pair->alone = false;
      rt.push_back(pair);
    }
    iter++;
    if (iter == pairs.end())
      break;
  }
  return (rt);
}

std::vector<r_pair *> insertions(std::vector<r_pair *> array,
                                 r_pair *left_out) {
  ulong current = 0;
  ulong prev = 0;
  std::vector<r_pair *> rt;
  std::vector<r_pair *>::iterator pushed = array.begin();
  std::vector<r_pair *>::iterator sorted = array.begin();

  while (true) {
    ulong in_pos = nex_jac_number(current, prev);
    if (in_pos == 1) {
      if ((*pushed)->alone == false) {
        rt.push_back((*pushed)->rest_smaller);
      }
      rt.push_back((*pushed)->rest_bigger);
      continue;
    }
    if (current > array.size())
      in_pos = array.size();

    if (prev >= array.size())
      break;
    for (ulong i = prev; i < in_pos; i++) {
      pushed++;
      if (pushed == array.end())
        break;
      rt.push_back((*pushed)->rest_bigger);
    }
    std::vector<r_pair *>::iterator unsorted = pushed;
    if (unsorted == array.end())
      unsorted--;
    while (unsorted != sorted) {
      if ((*unsorted)->alone == false) {
        std::vector<r_pair *>::iterator pos = std::lower_bound(
            rt.begin(),
            std::find(rt.begin(), rt.end(), (*unsorted)->rest_bigger),
            (*unsorted)->rest_smaller, r_pair_comp);
        rt.insert(pos, (*unsorted)->rest_smaller);
      }
      unsorted--;
    }

    sorted = pushed;
  }

  if (left_out != NULL) {
    std::vector<r_pair *>::iterator pos =
        std::lower_bound(rt.begin(), rt.end(), left_out, r_pair_comp);
    rt.insert(pos, left_out->rest_bigger);
    delete left_out;
  }

  for (std::vector<r_pair *>::iterator i = array.begin(); i != array.end();
       i++) {
    delete *i;
  }
  return (rt);
}

std::vector<int> last_insercion(std::vector<r_pair *> array, r_pair *left_out) {
  ulong current = 0;
  ulong prev = 0;
  std::vector<int *> tmp;
  std::vector<r_pair *>::iterator pushed = array.begin();
  std::vector<r_pair *>::iterator sorted = array.begin();

  while (true) {
    ulong in_pos = nex_jac_number(current, prev);
    if (in_pos == 1) {
      if ((*pushed)->alone == false) {
        tmp.push_back(&(*pushed)->smaller);
      }
      tmp.push_back(&(*pushed)->bigger);
      continue;
    }
    if (current > array.size())
      in_pos = array.size();

    if (prev >= array.size())
      break;
    for (ulong i = prev; i < in_pos; i++) {
      pushed++;
      if (pushed == array.end())
        break;
      tmp.push_back(&(*pushed)->bigger);
    }
    std::vector<r_pair *>::iterator unsorted = pushed;
    if (unsorted == array.end())
      unsorted--;
    while (unsorted != sorted) {
      if ((*unsorted)->alone == false) {
        std::vector<int *>::iterator pos = std::lower_bound(
            tmp.begin(),
            std::find(tmp.begin(), tmp.end(), &(*unsorted)->bigger),
            &(*unsorted)->smaller, int_addr_cmp);
        tmp.insert(pos, &(*unsorted)->smaller);
      }
      unsorted--;
    }

    sorted = pushed;
  }

  if (left_out != NULL) {
    std::vector<int *>::iterator pos = std::lower_bound(
        tmp.begin(), tmp.end(), &left_out->bigger, int_addr_cmp);
    tmp.insert(pos, &left_out->bigger);
  }

  std::vector<int> rt;

  for (std::vector<int *>::iterator i = tmp.begin(); i != tmp.end(); i++) {
    rt.push_back(**i);
  }
  for (std::vector<r_pair *>::iterator i = array.begin(); i != array.end();
       i++) {
    delete *i;
  }
  delete left_out;
  return (rt);
}

std::vector<int> vec_pmerge_me(std::vector<int> &vec) {

  if (vec.size() == 1) {
    return vec;
  }

  std::vector<r_pair *> pair = create_pair(vec);
  std::vector<r_pair *> left_out;
  if (pair.back()->alone == true) {
    left_out.push_back(pair.back());
    pair.pop_back();
  } else {
    left_out.push_back(NULL);
  }
  while (pair.size() != 1) {
    pair = create_pair(pair);
    if (pair.back()->alone == true) {
      left_out.push_back(pair.back());
      pair.pop_back();
    } else {
      left_out.push_back(NULL);
    }
  }
  while (pair[0]->rest_bigger != NULL) {
    pair = insertions(pair, left_out.back());
    left_out.pop_back();
  }

  std::vector<int> rt = last_insercion(pair, left_out.back());
  return (rt);
}
