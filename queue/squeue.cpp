#include <iostream>
#include "abstract_queue.h"

const unsigned MAX_QUEUE = 100;

template <typename T>
class StaticQueue : public AbstractQueue<T> {

  T a[MAX_QUEUE];
  int front, back;

  // проверка дали масивът е запълнен
  bool full() const { return back == MAX_QUEUE - 1; }
  
public:
  StaticQueue() : front(0), back(-1) {}
  
  // проверка за празнота на опашка
  bool empty() const { return front == back + 1; }

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
    std::cerr << "Опит за добавяне в пълна опашка!\n";
    return false;
  }
  
  a[++back] = x;
  return true;
}

template <typename T>
T StaticQueue<T>::dequeue() {
  if (empty()) {
    std::cerr << "Опит за изваждане от празна опашка!\n";
    return T();
  }
  return a[front++];
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
