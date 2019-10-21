#include <vector>
#include <iostream>
#include "lstack.cpp"

using Position   = std::pair<unsigned, unsigned>;
using Path       = LinkedStack<Position>;
using Chessrow   = std::vector<bool>;
using Chessboard = std::vector<Chessrow>;
using StackFrame = LinkedStack<Position>;
using StepStack  = LinkedStack<StackFrame>;

class HorseWalker {

  Chessboard board;
  Path path;
  StepStack stack;

  bool insideRange(unsigned c) const { return c < board.size(); }

  bool insideBoard(Position p) const { return insideRange(p.first) && insideRange(p.second); }

  void printPath() const;

public:

  HorseWalker(unsigned n);

  void printBoard() const;

  bool findPathRec(Position start, Position end);
  bool findPathStack(Position start, Position end);
  
};

std::ostream& operator<<(std::ostream& os, Position const& p);
