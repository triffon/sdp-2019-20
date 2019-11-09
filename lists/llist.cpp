template <typename T>
struct LinkedListElement {
  T data;
  LinkedListElement* next;
};

template <typename T>
class LinkedList;

template <typename T>
class LinkedListIterator {
  friend class LinkedList<T>;
  using LLE = LinkedListElement<T>;
  using I   = LinkedListIterator<T>;
  LLE* ptr;
public:
  LinkedListIterator(LLE* p = nullptr) : ptr(p) {}

  I next() const {
    if (!valid())
      return *this;
    
    return I(ptr->next);
  }

  bool valid() const { return ptr != nullptr; }

  T const& getConst() const { return ptr->data; } // !!! не правим проверка за коректност
  T&       get()      const { return ptr->data; } // !!! не правим проверка за коректност

  // it <-> it.valid();
  operator bool() const { return valid(); }

  // ++it
  I& operator++() {
    return (*this = next());
  }
  
  // it++ 
  I operator++(int) {
    I save = *this;
    ++(*this);
    return save;
  }

  // *it = 3;
  T& operator*() { return get(); }

  bool operator==(I const& it) const { return ptr == it.ptr; }
  bool operator!=(I const& it) const { return !(*this == it); }

  I& operator+=(unsigned n) {
    for(unsigned i = 0; i < n; i++)
      ++(*this);
    return *this;
  }
};

template <typename T>
class LinkedList {
  using LLE = LinkedListElement<T>;
  LLE *front, *back;
public:

  using I   = LinkedListIterator<T>;

  LinkedList() : front(nullptr), back(nullptr) {}

  LinkedList(LinkedList const& ll);
  LinkedList& operator=(LinkedList const& ll);
  ~LinkedList() {}

  bool empty() const { return front == nullptr; }

  bool insertBefore(I const& it, T const& x);
  bool insertAfter (I const& it, T const& x);

  bool deleteBefore(I const& it) { T tmp; return deleteBefore(it, tmp); }
  bool deleteAt    (I const& it) { T tmp; return deleteAt    (it, tmp); }
  bool deleteAfter (I const& it) { T tmp; return deleteAfter (it, tmp); }

  bool deleteBefore(I const& it, T& x);
  bool deleteAt    (I const& it, T& x);
  bool deleteAfter (I const& it, T& x);

  bool insertFirst(T const& x) { return insertBefore(begin(), x); }
  bool insertLast (T const& x) { return insertAfter (end()  , x); }

  bool deleteFirst(T& x) { return deleteAt(begin(), x); }
  bool deleteLast (T& x) { return deleteAt(end(),   x); }

  bool deleteFirst() { return deleteAt(begin()); }
  bool deleteLast () { return deleteAt(end());   }
  
  T const& getAt(I const& it) const { return it.getConst(); }
  T&       getAt(I const& it)       { return it.get();      }

  I begin() const { return I(front); }
  I end()   const { return I();      }

  LinkedList<T>& operator+=(T const& x) { insertLast(x); return *this; }
};

// O(1) по време и памет
template <typename T>
bool LinkedList<T>::insertAfter(I const& it, T const& x) {
  // it.ptr == nullptr <-> искаме да добавяме в края
  if (empty()) {
    // front == back == nullptr
    front = back = new LLE{x, nullptr};
    return true;
  }

  LLE* p = new LLE{x, nullptr};

  if (!it) {
    // искаме да добавяме в края
    back->next = p;
    back = p;
  } else {
    // искаме да добавяме някъде по средата
    p->next = it.ptr->next;
    it.ptr->next = p;
  }
  return true;
}

// O(1) по време и по памет
template <typename T>
bool LinkedList<T>::deleteAfter(I const& it, T& x) {
  if (!it)
    // не можем да изтриваме след невалиден итератор
    return false;
  // it.valid()
  
  LLE* p = it.ptr->next;
  
  if (!p)
    // не можем да изтриваме след края
    return false;
  // p != nullptr
  
  it.ptr->next = p->next;
  x = p->data;
  delete p;
  return true;
}
