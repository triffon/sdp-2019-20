#include <iostream>
#include "llist.cpp"

class SElement {
public:
  virtual void print(std::ostream& = std::cout) const = 0;

  virtual void collect(LinkedList<int>&) const = 0;

  virtual ~SElement() {}
};

class SInt : public SElement {
private:
  int data;

public:

  SInt(int d = 0) : data(d) {}
  
  void print(std::ostream& os = std::cout) const { os << data; }

  void collect(LinkedList<int>& l) const { l += data; }
};

using SLL = LinkedList<SElement*>;

class SList : private SLL, public SElement {
public:
  SList* add(SElement* se) {
    insertLast(se);
    return this;
  }

  void print(std::ostream& os = std::cout) const {
    os << '(';
    
    /*
      Вярно, но извежда интервал в повече

      for(SElement* se : *this) {
        se->print(os);
        os << ' ';
      }
    */
    typename SLL::I it = begin();
    if (it) {
      // имаме поне един елемент
      (*it++)->print(os);
      for(; it; ++it) {
        os << ' ';
        (*it)->print(os);
      }
    }
    os << ')';
  }

  void collect(LinkedList<int>& l) const {
    for(SElement* se : *this)
      se->collect(l);
  }

  ~SList() {
    for(SElement* se : *this)
      delete se;
  }
};
