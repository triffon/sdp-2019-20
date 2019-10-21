#ifndef __SQUEUE_CPP
#define __SQUEUE_CPP

#include <iostream>
#include "abstract_queue.h"

const unsigned MAX_QUEUE = 100;

template <typename T>
class StaticQueue : public AbstractQueue<T> {

  T a[MAX_QUEUE];
  int front, back;

  // проверка дали масивът е запълнен
  bool full() const { return !empty() && front == (back + 1) % capacity(); }

  // капацитет на масива
  unsigned capacity() const { return MAX_QUEUE; }

  // установяване на празна опашка
  void setEmpty() { front = 0; back = -1; }
  
public:
  StaticQueue() { setEmpty(); }
  
  // проверка за празнота на опашка
  bool empty() const { return front == 0 && back == -1; }

  // включване на елемент и връща дали е било успешно
  bool enqueue(T const& x);

  // изключване на елемент
  T dequeue();

  // поглеждане в началото на опашката
  T const& head() const;

  // поглеждане в началото на опашката с възможност за промяна
  T& head();
  
};

template <typename T>
bool StaticQueue<T>::enqueue(T const& x) {
  if (full()) {
    std::cerr << "Опит за добавяне на " << x << " в пълна опашка!\n";
    std::cerr << front << ' ' << back << std::endl;
    return false;
  }

  a[(++back) %= capacity()] = x;
  
  // if (back == capacity())
  //   back = 0;
  return true;
}

template <typename T>
T StaticQueue<T>::dequeue() {
  if (empty()) {
    std::cerr << "Опит за изваждане от празна опашка!\n";
    return T();
  }
  //  return a[front++];
  T result = head();
  (++front) %= capacity();
  
  if (full())
    // ако опашката некоректно казва, че е запълнена, значи всъщност е празна
    setEmpty();
  return result;
}

template <typename T>
T const& StaticQueue<T>::head() const {
  if (empty()) {
    std::cerr << "Опит за поглеждане в празна опашка!\n";
    return a[0]; // лошо!!!
  }
  
  return a[front];
}

template <typename T>
T& StaticQueue<T>::head() {
  if (empty()) {
    std::cerr << "Опит за поглеждане в празна опашка!\n";
    return a[0]; // лошо!!!
  }
  
  return a[front];
}

#endif
