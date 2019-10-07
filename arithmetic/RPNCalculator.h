#include <string>
#include "lstack.cpp"

using ResultsStack = LinkedStack<double>;

class RPNCalculator {
  ResultsStack results;

  bool isDigit(char c) const { return '0' <= c && c <= '9'; }

  int digitValue(char c) const { return c - '0'; }

  double apply(char op, double larg, double rarg) const;
public:
  double calculateRPN(std::string rpn);
};
