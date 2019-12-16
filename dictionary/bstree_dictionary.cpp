#ifndef __BSTREE_DICTIONARY_H
#define __BSTREE_DICTIONARY_H

#include "dictionary.h"
#include "key_value_pair.cpp"
#include "bstree.cpp"

template <typename K, typename V>
class BSTreeDictionary : public Dictionary<K, V>, BSTree<KeyValuePair<K, V>> {
  using KVP = KeyValuePair<K, V>;
  using P = BinTreePosition<KVP>;
  using BST = BSTree<KVP>;

  using BST::search;
  using BST::insert;
  
public:
  // търси стойността, свързана с ключа key, ако я има, с възможност за промяна
  V* lookup(K const& key) {
    P pos = search(key);
    if (!pos)
      return nullptr;
    return &(*pos).getValue();
  }

  // добавя стойността value към ключа key
  bool add(K const& key, V const& value) {
    return insert(KVP(key, value));
  }

  // изтрива ключа key и свързаната с него стойност
  bool remove(K const& key) {
    return BST::remove(key);
  }

  // вектор от всички ключове
  std::vector<K> keys() const { return std::vector<K>(); }

  // вектор от всички стойности
  std::vector<K> values() const { return std::vector<V>(); }
};

#endif
