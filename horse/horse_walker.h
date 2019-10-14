#include <vector>

using Position   = std::pair<unsigned, unsigned>;
using Chessrow   = std::vector<bool>;
using Chessboard = std::vector<Chessrow>;

class HorseWalker {

  Chessboard board;

  bool insideRange(unsigned c) const { return c < board.size(); }

  bool insideBoard(Position p) const { return insideRange(p.first) && insideRange(p.second); }

public:

  HorseWalker(unsigned n);

  void printBoard() const;

  bool findPathRec(Position start, Position end);
  
};
