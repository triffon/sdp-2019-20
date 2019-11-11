template <typename T>
struct DoubleLinkedListElement {
  T data;
  DoubleLinkedListElement *next, *prev;
};

template <typename T>
class DoubleLinkedList;

template <typename T>
class DoubleLinkedListIterator {
  friend class DoubleLinkedList<T>;
  using DLLE = DoubleLinkedListElement<T>;
  using I   = DoubleLinkedListIterator<T>;
  DLLE* ptr;
public:

  using Type   = T;

  DoubleLinkedListIterator(DLLE* p = nullptr) : ptr(p) {}

  I next() const {
    if (!valid())
      return *this;

    return I(ptr->next);
  }

  I prev() const {
    if (!valid())
      return *this;

    return I(ptr->prev);
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

  // --it
  I& operator--() {
    return (*this = prev());
  }

  // it--
  I operator--(int) {
    I save = *this;
    --(*this);
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

  I& operator-=(unsigned n) {
    for(unsigned i = 0; i < n; i++)
      --(*this);
    return *this;
  }
};

template <typename T>
class DoubleLinkedList {
  using DLLE = DoubleLinkedListElement<T>;
  DLLE *front, *back;

  void erase();

public:

  using I      = DoubleLinkedListIterator<T>;
  using Type   = T;

  DoubleLinkedList() : front(nullptr), back(nullptr) {}

  DoubleLinkedList(DoubleLinkedList const& ll);
  DoubleLinkedList& operator=(DoubleLinkedList const& ll);
  ~DoubleLinkedList() { erase(); }

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

  DoubleLinkedList<T>& operator+=(T const& x) { insertLast(x); return *this; }

  // залепва елементите на l в края на списъка
  void append(DoubleLinkedList const& l);

  // присвоява си елементите на l като ги залепва в края на списъка
  void appendAssign(DoubleLinkedList& l);
};

template <typename T>
bool DoubleLinkedList<T>::insertAfter(I const& it, T const& x) {
  if (empty()) {
    front = back = new DLLE{x, nullptr, nullptr};
    return true;
  }

  // !empty()

  if (!it || it.ptr == back) {
    // добавяме след края на списъка
    back = new DLLE{x, nullptr, back};
    back->prev->next = back;
    return true;
  }

  // it.ptr != nullptr
  // it.ptr->next != nullptr
  DLLE *p = new DLLE{x, it.ptr->next, it.ptr};
  p->next->prev = p;
  p->prev->next = p;
  return false;
}

template <typename T>
bool DoubleLinkedList<T>::deleteAfter(I const& it, T& x) {
  return false;
}

// O(n) по време и O(1) по памет
template <typename T>
bool DoubleLinkedList<T>::insertBefore(I const& it, T const& x) {
  if (empty())
    return insertLast(x);

  // вмъкване преди първи елемент
  if (it.ptr == front              ||    // посочили сме за итератор първия елемент
      (!it && back->prev == nullptr)) {  // искаме да вмъкваме преди последния елемент, но имаме само един елемент!
    // добавяме преди началото на списъка
    front = new DLLE{x, front, nullptr};
    front->next->prev = front;
    return true;
  } 

  // не вмъкваме преди първи елемент
  if (!it)
    // искаме да вмъкваме преди последния елемент
    return insertAfter(I(back->prev), x);

  // общ случай
  return insertAfter(it.prev(), x);
}

template <typename T>
bool DoubleLinkedList<T>::deleteAt(I const& it, T& x) {
  if (it.ptr->prev != nullptr)
    it.ptr->prev->next = it.ptr->next;
  else
    // изтриваме първия елемент, трябва да преместим front
    front = it.ptr->next;

  if (it.ptr->next != nullptr)
    it.ptr->next->prev = it.ptr->prev;
  else
    // изтриваме последния елемент, трябва да преместим back
    back = it.ptr->prev;

  // изтриването на последния елемент работи както се очаква
  x = it.ptr->data;
  delete it.ptr;
  return true;
}

// O(n) по време и O(1) по памет
template <typename T>
bool DoubleLinkedList<T>::deleteBefore(I const& it, T& x) {
  return false;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList const& l) : front(nullptr), back(nullptr) {
  append(l);
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList const& l) {
  if (this != &l) {
    erase();
    append(l);
  }
  return *this;
}

template <typename T>
void DoubleLinkedList<T>::append(DoubleLinkedList const& l) {
  for(T const& x : l)
    insertLast(x);
}

template <typename T>
void DoubleLinkedList<T>::erase() {
  while (!empty())
    deleteFirst();
}

template <typename T>
void DoubleLinkedList<T>::appendAssign(DoubleLinkedList& l) {
}
