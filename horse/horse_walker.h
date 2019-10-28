#include <vector>
#include <iostream>
#include "lstack.cpp"
#include "lqueue.cpp"

using Position   = std::pair<int, int>;
using Path       = LinkedStack<Position>;
using Chessrow   = std::vector<bool>;
using Chessboard = std::vector<Chessrow>;
using StackFrame = LinkedStack<Position>;
using FrameStack = LinkedStack<StackFrame>;
using Queue      = LinkedQueue<Position>;
using Step       = std::pair<Position, Position>;
using StepStack  = LinkedStack<Step>; 

class HorseWalker {

  Chessboard board;
  Path path;
  FrameStack stack;
  Queue queue;

  bool insideRange(unsigned c) const { return c < board.size(); }

  bool insideBoard(Position p) const { return insideRange(p.first) && insideRange(p.second); }

  void printPath() const;

public:

  HorseWalker(unsigned n);

  void printBoard() const;

  bool findPathRec(Position start, Position end);
  bool findPathStack(Position start, Position end);
  bool findPathQueue(Position start, Position end);
  
};

std::ostream& operator<<(std::ostream& os, Position const& p);
