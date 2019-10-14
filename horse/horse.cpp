#include <cmath>
#include <iostream>
#include "horse_walker.h"

int main() {
  std::cout << "------------------------------------------\n";
  // std::cout << HorseWalker(4).findPathRec  ({0, 0}, {2, 2}) << std::endl;
  // std::cout << HorseWalker(4).findPathStack({0, 0}, {2, 2}) << std::endl;
  // std::cout << HorseWalker(4).findPathRec  ({0, 0}, {3, 3}) << std::endl;
  // std::cout << HorseWalker(4).findPathStack({0, 0}, {3, 3}) << std::endl;
  std::cout << HorseWalker(4).findPathRec  ({0, 0}, {0, 2}) << std::endl;
  std::cout << HorseWalker(4).findPathStack({0, 0}, {0, 2}) << std::endl;
  /*
  const int N = 4;
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++) {
      std::cerr << Position(i, j) << std::endl;
      HorseWalker(N).findPathStack({0, 0}, {i, j});
      }*/
  std::cout << "==========================================\n";

  return 0;
}
