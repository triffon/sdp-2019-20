#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "bstree_dictionary.cpp"
#include "linked_hash.cpp"

using TestDictionary = BSTreeDictionary<int, int>;

unsigned simpleHashFunction(int const& x) {
  return x;
}

#define TEST_BOTH BSTreeDictionary<int, int>, LinkedHash<int, int, simpleHashFunction>

#include "dictionary_tests.h"
