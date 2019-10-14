#include <cmath>
#include "RPNCalculator.h"

double RPNCalculator::apply(char op, double larg, double rarg) const {
  switch (op) {
  case '+' : return larg + rarg;
  case '-' : return larg - rarg;
  case '*' : return larg * rarg;
  case '/' : return larg / rarg;
  case '^' : return pow(larg, rarg);
  default  : return 0;
  }
}

double RPNCalculator::calculateRPN(std::string rpn) {
  for(char c : rpn) {
    if (isDigit(c))
      results.push(digitValue(c));
    else {
      double rarg = results.pop();
      double larg = results.pop();
      results.push(apply(c,larg,rarg));
    }
  }
  return results.pop();
}

std::string RPNCalculator::toRPN(std::string expr) {
  std::string rpn;
  for(char c : expr) {
    if (isDigit(c))
      rpn.push_back(c);
    else if (c != ')')
      ops.push(c);
    else
      // c == ')'
      while ((c = ops.pop()) != '(')
        rpn.push_back(c);
  }
  while (!ops.empty())
    rpn.push_back(ops.pop());
  return rpn;
}
