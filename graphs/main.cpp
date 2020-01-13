#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "graph.cpp"

unsigned simpleHashFunction(int const& x) {
  return x;
}

using TestGraph = Graph<int, simpleHashFunction>;

#include "graph_tests.h"

template <typename V, HashFunction<V> hashFunction>
std::vector<V> childless(Graph<V, hashFunction>& g) {
  std::vector<V> result;
  for(V u : g.vertices())
    if (g.successors(u).empty())
      result.push_back(u);
  return result;
}

#include "graph_problems_tests.h"

