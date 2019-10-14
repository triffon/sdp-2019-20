#include <cmath>
#include <iostream>
#include "horse_walker.h"

bool HorseWalker::findPathRec(Position start, Position end) {
  if (start == end)
    // намерихме път
    return true;

  if (!insideBoard(start))
    // излязохме извън дъската
    return false;

  if (board[start.first][start.second])
    // вече сме стъпвали тук
    return false;

  board[start.first][start.second] = true;

  for(int dx = -2; dx <= 2; dx++)
    if (dx != 0)
      for(int sign : {-1, 1}) {
        int dy = sign * (3 - std::abs(dx));
        Position newstart(start.first + dx, start.second + dy);
        if (findPathRec(newstart, end))
          return true;
      }

  return false;
}

int main() {
  HorseWalker hw(8);
  hw.printBoard();
  std::cout << hw.findPathRec({0, 0}, {2, 2}) << std::endl;
  return 0;
}
