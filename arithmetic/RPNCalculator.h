#include <string>
#include "lstack.cpp"

using ResultStack = LinkedStack<double>;
using OpStack      = LinkedStack<char>;

class RPNCalculator {
  ResultStack results;
  OpStack     ops;

  bool isDigit(char c) const { return '0' <= c && c <= '9'; }

  int digitValue(char c) const { return c - '0'; }

  double apply(char op, double larg, double rarg) const;
public:
  
  double calculateRPN(std::string rpn);

  std::string toRPN(std::string expr);

  double calculate(std::string expr) { return calculateRPN(toRPN(expr)); }
};
