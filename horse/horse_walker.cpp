#include <iostream>
#include "horse_walker.h"

HorseWalker::HorseWalker(unsigned n) {
  for(int i = 0; i < n; i++)
    board.push_back(Chessrow(n));
}

void HorseWalker::printBoard() const {
  /*  for(int i = 0; i < board.size(); i++) {
    for(int j = 0; j < board.size(); j++)
      std::clog << (board[i][j] ? '*' : '_');
    std::clog << std::endl;
    }*/
  for(auto row : board) {
    for(auto b : row)
      std::clog << (b ? '*' : '_');
    std::clog << std::endl;
  }
}
