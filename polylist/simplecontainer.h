#ifndef __SIMPLECONTAINER_H
#define __SIMPLECONTAINER_H

template <typename T>
class SimpleContainer {
public:
  // включване на елемент
  virtual bool insert(T const&) = 0;

  // изключване на елемент
  virtual bool remove(T&) = 0;

  virtual ~SimpleContainer() {}
};

#endif
