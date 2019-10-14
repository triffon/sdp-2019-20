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

void RPNCalculator::popAndApply(char c) {
  double rarg = results.pop();
  double larg = results.pop();
  results.push(apply(c,larg,rarg));
}

double RPNCalculator::calculateRPN(std::string rpn) {
  for(char c : rpn)
    if (isDigit(c))
      results.push(digitValue(c));
    else
      popAndApply(c);
  return results.pop();
}

std::string RPNCalculator::toRPN(std::string expr) {
  std::string rpn;
  for(char c : expr) {
    if (isDigit(c))
      rpn.push_back(c);
    else if (c == '(')
      ops.push(c);
    else if (c != ')') {
      // избутваме операциите с >= приоритет
      while (!ops.empty() && priority(ops.peek()) >= priority(c)) {
        // std::clog << "Избутваме " << ops.peek() << std::endl;
        rpn.push_back(ops.pop());
      }
      ops.push(c);
    }
    else
      // c == ')'
      while ((c = ops.pop()) != '(')
        rpn.push_back(c);
  }
  while (!ops.empty())
    rpn.push_back(ops.pop());
  return rpn;
}

int RPNCalculator::priority(char op) const {
  switch(op) {
  case '+':
  case '-': return 1;
  case '*':
  case '/': return 2;
  case '^': return 3;
  default : return 0;
  }
}



double RPNCalculator::calculateDirect(std::string expr) {
  for(char c : expr) {
    if (isDigit(c))
      results.push(digitValue(c));
    else if (c == '(')
      ops.push(c);
    else if (c != ')') {
      // избутваме операциите с >= приоритет
      while (!ops.empty() && priority(ops.peek()) >= priority(c)) {
        // std::clog << "Избутваме " << ops.peek() << std::endl;
        popAndApply(ops.pop());
      }
      ops.push(c);
    }
    else
      // c == ')'
      while ((c = ops.pop()) != '(')
        popAndApply(c);
  }
  while (!ops.empty())
    popAndApply(ops.pop());
  return results.pop();
}
