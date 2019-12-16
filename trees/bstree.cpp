#ifndef __BSTREE_CPP
#define __BSTREE_CPP

#include "bintree.cpp"

template <typename T>
class BSTree : public BinTree<T> {
public:
  using typename BinTree<T>::P;

  using BinTree<T>::rootPos;
  using BinTree<T>::assignFrom;

  P search(T const& x) {
    P pos = rootPos();
    while (pos && *pos != x)
      if (x < *pos)
        --pos;
      else
        ++pos;
    // !pos      --> false
    // *pos == x --> true
    return pos;
  }

  bool insert(T const& x) {
    P pos = search(x);
    if (pos)
      // елементът вече присъства, не можем да го включим пак
      return false;

    // pos е позицията, където искаме да вмъкнем
    BinTree<T> leaf = x;
    assignFrom(pos, leaf.rootPos());
    return true;
  }

  bool remove(T const& x) {
    P pos = search(x);
    if (!pos)
      return false;

    if (!-pos) {
      assignFrom(pos, +pos);
      return true;
    }

    if (!+pos) {
      assignFrom(pos, -pos);
      return true;
    }

    // -pos и +pos са валидни позиции
    // търсим най-левия възел в дясното поддърво
    P m = +pos; // започваме от корена на дясното поддърво
    while (-m) --m;
    // !-m
    // записваме стойността на m в корена
    *pos = *m;
    // нека m да си открадне собственото дясно поддърво
    // т.е. сведохме до случая, в който изтриваме възел, който няма ляво поддърво
    assignFrom(m, +m);
    return true;
  }
};

#endif
