#include "lstack.cpp"
#include "simplecontainer.h"

template <typename T>
class SimpleStack : private LinkedStack<T>, public SimpleContainer<T> {
public:
  using LinkedStack<T>::push;
  using LinkedStack<T>::pop;
  using LinkedStack<T>::empty;
  
  // включване на елемент
  bool insert(T const& x) {
    return push(x);
  }

  // изключване на елемент
  bool remove(T& x) {
    if (LinkedStack<T>::empty())
      return false;
    x = LinkedStack<T>::pop();
    return true;
  }
};
