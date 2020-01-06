#ifndef __SET_H
#define __SET_H

template <template <typename, typename> class Dictionary, typename T>
class Set {
  Dictionary<T, bool> dict;
public:
  bool empty() const {
    return dict.empty();
  }

  bool insert(T const& x) {
    return dict.add(x, false);
  }

  bool remove(T const& x) {
    return dict.remove(x);
  }

  bool contains(T const& x) {
    return dict.lookup(x) != nullptr;
  }

  std::vector<T> elements() const {
    return dict.keys();
  }
};

#endif
