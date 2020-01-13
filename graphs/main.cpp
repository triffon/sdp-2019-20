#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <algorithm>
#include <iostream>

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

template <typename V, HashFunction<V> hashFunction>
bool dfsPathRec(Graph<V, hashFunction>& g, V const& u, V const& v, Path<V>& path) {
  // дали вече този връх го има в пътя?
  if (std::find(path.begin(), path.end(), u) != path.end())
    return false;

  // няма да зациклим, добавяме го в пътя
  path.push_back(u);

  if (u == v)
    // намерихме път!
    return true;

  // търсим път от някой от наследниците w на u до v
  for(V w : g.successors(u))
    if (dfsPathRec(g, w, v, path))
      return true;

  // от никой от наследниците на u не можем да стигнем до v
  // отказваме се от u в пътя

  path.pop_back();
  return false;
}

template <typename V>
void printPath(Path<V> const& path) {
  for(V v : path)
    std::cout << v << " ";
  std::cout << std::endl;
}

template <typename V, HashFunction<V> hashFunction>
Path<V> dfsPath(Graph<V, hashFunction>& g, V const& u, V const& v) {
  Path<V> result;
  dfsPathRec(g, u, v, result);
  printPath(result);
  return result;
}

#include "graph_problems_tests.h"

