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

  // O(1) по време и памет
  bool insertFirst(T const& x) { return insertBefore(begin(), x); }
  bool insertLast (T const& x) { return insertAfter (end()  , x); }

  // O(1) по време и памет
  bool deleteFirst(T& x) { return deleteAt(begin(), x); }
  bool deleteLast (T& x) { return deleteAt(end(),   x); }

  // O(1) по време и памет
  bool deleteFirst() { return deleteAt(begin()); }
  bool deleteLast () { return deleteAt(end());   }

  T const& getAt(I const& it) const { return it.getConst(); }
  T&       getAt(I const& it)       { return it.get();      }

  I begin() const { return I(front); }
  I end()   const { return I();      }

  LinkedList<T>& operator+=(T const& x) { insertLast(x); return *this; }

private:

  I findPrev(I const&);
};

// O(1) по време и памет
template <typename T>
bool LinkedList<T>::insertAfter(I const& it, T const& x) {
  if (empty()) {
    return insertFirst(x);
  }

  // it.ptr == nullptr <-> искаме да добавяме в края
  LLE* p = new LLE{x, nullptr};

  if (!it || it.ptr == back) {
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

  if (back == p)
    // изтриваме последния елемент!
    back = it.ptr;

  delete p;
  return true;
}

// O(n) по време и O(1) по памет
template <typename T>
bool LinkedList<T>::insertBefore(I const& it, T const& x) {
  if (it == begin()) {
    // вмъкваме в началото: специален случай
    LLE* p = new LLE{x, front};
    front = p;
    if (back == nullptr)
      // вмъкваме в празен списък
      back = p;
    return true;
  }
  return insertAfter(findPrev(it), x);
}

// O(n) по време и O(1) по памет
template <typename T>
LinkedListIterator<T> LinkedList<T>::findPrev(LinkedListIterator<T> const& it) {
  if (!it)
    return I(back);
  I result = begin();
  while (result && result.ptr->next != it.ptr)
    ++result;
  // result.ptr->next == it.ptr
  return result;
}

// O(n) по време и O(1) по памет
template <typename T>
bool LinkedList<T>::deleteAt(I const& it, T& x) {
  // ако it.ptr е невалиден, имаме предвид изтриване на последния елемент
  if (!it)
    return deleteAfter(findPrev(I(back)), x);

  // можем да считаме, че списъкът не е празен
  if (it == begin()) {
    x = front->data;
    LLE* p = front;
    front = front->next;
    if (back == p)
      // изтриваме последния елемент от списъка
      back = nullptr;
    delete p;
    return true;
  }

  return deleteAfter(findPrev(it), x);
}
