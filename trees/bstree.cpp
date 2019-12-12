#ifndef __BSTREE_CPP
#define __BSTREE_CPP

#include "bintree.cpp"

template <typename T>
class BSTree : public BinTree<T> {
public:
  using typename BinTree<T>::P;

  P search(T const& x) const {
    P pos = this->rootPos();
    while (pos && *pos != x)
      if (x < *pos)
        --pos;
      else
        ++pos;
    // !pos      --> false
    // *pos == x --> true
    return pos;
  }
};

#endif
