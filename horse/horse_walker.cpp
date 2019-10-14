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

std::ostream& operator<<(std::ostream& os, Position const& p) {
  return os << '(' << p.first << ", " << p.second << ')';
}


bool HorseWalker::findPathRec(Position start, Position end) {
  if (!insideBoard(start))
    // излязохме извън дъската
    return false;

  if (board[start.first][start.second])
    // вече сме стъпвали тук
    return false;

  std::clog << "Стъпка напред върху " << start << std::endl;
  path.push(start);
  board[start.first][start.second] = true;

  if (start == end) {
    // намерихме път
    printPath();
    return true;
  }

  for(int dx = -2; dx <= 2; dx++)
    if (dx != 0)
      for(int sign : {-1, 1}) {
        int dy = sign * (3 - std::abs(dx));
        Position newstart(start.first + dx, start.second + dy);
        if (findPathRec(newstart, end))
          return true;
      }

  std::clog << "Стъпка назад от " << start << std::endl;
  path.pop();
  return false;
}

void HorseWalker::printPath() const {
  Path copy = path;
  std::clog << copy.pop();
  while (!copy.empty())
    std::clog << " <- " << copy.pop();
  std::clog << std::endl;
}
