#ifndef __LINKED_HASH_CPP
#define __LINKED_HASH_CPP

#include "dictionary.h"
#include "key_value_pair.cpp"
#include "llist.cpp"

template <typename K>
using HashFunction = unsigned (*)(K const&);

template <typename K, typename V, HashFunction<K> hashFunction, unsigned HASH_SIZE = 101>
class LinkedHash : public Dictionary<K, V> {
  LinkedList<KeyValuePair<K,V>> table[HASH_SIZE];
public:
  // търси стойността, свързана с ключа key, ако я има, с възможност за промяна
  V* lookup(K const& key) { return nullptr; }

  // добавя стойността value към ключа key
  bool add(K const& key, V const& value) { return false; }

  // изтрива ключа key и свързаната с него стойност
  bool remove(K const& key) { return false; }

  // вектор от всички ключове
  std::vector<K> keys() { return std::vector<K>(); }

  // вектор от всички стойности
  std::vector<V> values() { return std::vector<V>(); }
};

#endif
