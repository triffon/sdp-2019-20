#include "abstract_queue.h"

const unsigned MAX_QUEUE = 100;

template <typename T>
class StaticQueue : public AbstractQueue<T> {

  T a[MAX_QUEUE];
  int front, back;
  
public:
  StaticQueue() : back(-1), front(0) {}
  
  // проверка за празнота на опашка
  bool empty() const { return front == back + 1; }

  // включване на елемент и връща дали е било успешно
  bool enqueue(T const& x) { return true; }

  // изключване на елемент
  T dequeue() { return T(); }

  // поглеждане в началото на опашката
  T const& head() const { return T(); }

  // поглеждане в началото на опашката с възможност за промяна
  T& head() { return a[0]; } // !!! лошо !!!
  
};
