#include <vector>
#include <iostream>
#include "lstack.cpp"

using Position   = std::pair<unsigned, unsigned>;
using Path       = LinkedStack<Position>;
using Chessrow   = std::vector<bool>;
using Chessboard = std::vector<Chessrow>;

class HorseWalker {

  Chessboard board;
  Path path;

  bool insideRange(unsigned c) const { return c < board.size(); }

  bool insideBoard(Position p) const { return insideRange(p.first) && insideRange(p.second); }

  void printPath() const;

public:

  HorseWalker(unsigned n);

  void printBoard() const;

  bool findPathRec(Position start, Position end);
  
};

std::ostream& operator<<(std::ostream& os, Position const& p);
