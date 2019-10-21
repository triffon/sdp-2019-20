#ifndef __ABSTRACT_QUEUE_H
#define __ABSTRACT_QUEUE_H

template <typename T>
class AbstractQueue {
public:
  // проверка за празнота на опашка
  virtual bool empty() const = 0;

  // включване на елемент и връща дали е било успешно
  virtual bool enqueue(T const& x) = 0;

  // изключване на елемент
  virtual T dequeue() = 0;

  // поглеждане в началото на опашката
  virtual T const& head() const = 0;

  // поглеждане в началото на опашката с възможност за промяна
  virtual T& head() = 0;
};

#endif
