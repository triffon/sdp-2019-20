#include "lqueue.cpp"
#include "simplecontainer.h"

template <typename T>
class SimpleQueue : private LinkedQueue<T>, public SimpleContainer<T> {
public:
  using LinkedQueue<T>::enqueue;
  using LinkedQueue<T>::dequeue;  
  using LinkedQueue<T>::empty;  
  
  // включване на елемент
  bool insert(T const& x) { return enqueue(x); }

  // изключване на елемент
  bool remove(T& x) {
    if (empty())
      return false;
    x = dequeue();
    return true;
  }
};
