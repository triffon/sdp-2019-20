#include <cmath>
#include <iostream>
#include "horse_walker.h"

int main() {
  HorseWalker hw(4);
  hw.printBoard();
  std::cout << hw.findPathRec({0, 0}, {3, 3}) << std::endl;
  return 0;
}
