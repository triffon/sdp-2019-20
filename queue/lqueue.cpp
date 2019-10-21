#ifndef __LQUEUE_CPP
#define __LQUEUE_CPP

#include <iostream>
#include "abstract_queue.h"

template <typename T>
struct QueueElement {
  T data;
  QueueElement* next;
};

template <typename T>
class LinkedQueue : AbstractQueue<T> {
  QueueElement<T> *front, *back;

public:
  LinkedQueue() : front(nullptr), back(nullptr) {}
  
  // проверка за празнота на опашка
  bool empty() const { return front == nullptr; }

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
bool LinkedQueue<T>::enqueue(T const& x) {
  QueueElement<T>* p = new QueueElement<T>{x, nullptr};
  
  if (back != nullptr)
    // насочваме предпоследния елемент към новия последен само ако опашката не е празна
    back->next = p;
  else
    // иначе, ако опашката е празна, се нареждаме в началото
    front = p;
  
  back = p;
  return true;
}

template <typename T>
T LinkedQueue<T>::dequeue() {
  if (empty()) {
    std::cerr << "Опит за изключване от празна опашка\n";
    return T();
  }
  
  QueueElement<T>* p = front;
  T result = head();
  front = front->next;
  if (front == nullptr)
    // ако няма друг елемент в опашката, трябва и back да е nullptr
    back = nullptr;
  delete p;
  return result;
}

template <typename T>
T const& LinkedQueue<T>::head() const {
  if (empty())
    std::cerr << "Опит за поглеждане в празна опашка\n";

  return front->data;
}

template <typename T>
T& LinkedQueue<T>::head() {
  if (empty())
    std::cerr << "Опит за поглеждане в празна опашка\n";

  return front->data;
}

#endif
