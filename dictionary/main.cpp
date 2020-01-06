#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "bstree_dictionary.cpp"
#include "linked_hash.cpp"

using TestDictionary = BSTreeDictionary<int, int>;

unsigned simpleHashFunction(int const& x) {
  return x;
}

#define TEST_BOTH BSTreeDictionary<int, int>, LinkedHash<int, int, simpleHashFunction>

using TestDictionary = BSTreeDictionary<int, int>;

unsigned stringHashFunction(std::string const& s) {
  unsigned result = 0;
  unsigned i = 1;
  for(char c : s)
    result += (i++) * c;
  return result;
}

#define TEST_BOTH_STRING BSTreeDictionary<std::string, std::string>,\
                         LinkedHash<std::string, std::string, stringHashFunction>

#include "dictionary_tests.h"

#include "set.h"

template <typename T>
using BSTreeSet = Set<BSTreeDictionary, T>;

using BSTreeIntSet = BSTreeSet<int>;

template <typename K, typename V>
using LinkedHashSimple = LinkedHash<K, V, simpleHashFunction>;

using HashIntSet = Set<LinkedHashSimple, int>;

#define TEST_SET_ALL BSTreeIntSet, HashIntSet

#include "set_tests.h"
