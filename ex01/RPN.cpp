#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>

RPN::RPN() {}

RPN::~RPN() {}

int RPN::evaluate(const std::string &expression) {
  std::stack<int> stack;
  std::istringstream stream(expression);
  std::string token;

  while (stream >> token) {
    if (token == "+" || token == "-" || token == "*" || token == "/") {
      if (stack.size() < 2) {
        throw std::runtime_error("Error");
      }

      int b = stack.top();
      stack.pop();
      int a = stack.top();
      stack.pop();

      int result;
      if (token == "+") {
        result = a + b;
      } else if (token == "-") {
        result = a - b;
      } else if (token == "*") {
        result = a * b;
      } else if (token == "/") {
        if (b == 0) {
          throw std::runtime_error("Error");
        }
        result = a / b;
      }

      stack.push(result);
    } else {
      if (token.length() > 1 || token[0] < '0' || token[0] > '9') {
        throw std::runtime_error("Error");
      }
      stack.push(token[0] - '0');
    }
  }

  if (stack.size() != 1) {
    throw std::runtime_error("Error");
  }

  return stack.top();
}
