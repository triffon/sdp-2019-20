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

  bool deleteBefore(I const& it);
  bool deleteAt    (I const& it);
  bool deleteAfter (I const& it);

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
