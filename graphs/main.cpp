#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "graph.cpp"

unsigned simpleHashFunction(int const& x) {
  return x;
}

using TestGraph = Graph<int, simpleHashFunction>;

template <typename V>
using Path = std::vector<V>;

using TestPath = Path<int>;

#include "graph_tests.h"

template <typename V, HashFunction<V> hashFunction>
std::vector<V> childless(Graph<V, hashFunction>& g) {
  std::vector<V> result;
  for(V u : g.vertices())
    if (g.successors(u).empty())
      result.push_back(u);
  return result;
}

template <typename V, HashFunction<V> hashFunction>
bool isSymmetric(Graph<V, hashFunction>& g) {
  for(V u : g.vertices())
    for(V v : g.successors(u))
      if (!g.isEdge(v, u))
        return false;
  return true;
}

#include "graph_problems_tests.h"

