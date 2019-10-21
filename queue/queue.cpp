#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "squeue.cpp"
#include "lqueue.cpp"

// using TestQueue = StaticQueue<int>;
using TestQueue = LinkedQueue<int>;

#include "queue_tests.h"

template <typename T>
void removeHead(AbstractQueue<T>& q, T const& x) {
  if (q.head() == x)
    q.dequeue();
}

void hamming(int n) {
  TestQueue q2, q3, q5;
  std::cout << 1;
  q2.enqueue(2);
  q3.enqueue(3);
  q5.enqueue(5);
  for(int i = 2; i <= n; i++) {
    // 1. намираме най-малкото число в опашките и го извеждаме
    int minh = std::min(q2.head(), std::min(q3.head(), q5.head()));
    std::cout << ", " << minh;
    // 2. изваждаме го от всички опашки, където се намира
    removeHead(q2, minh);
    removeHead(q3, minh);
    removeHead(q5, minh);
    // 3. добавяме *2, *3, *5 в съответните опашки
    q2.enqueue(minh * 2);
    q3.enqueue(minh * 3);
    q5.enqueue(minh * 5);
  }
  std::cout << std::endl;
}

int main() {
  // пускане на тестовете
  doctest::Context().run();

  hamming(30);
  return 0;
}
