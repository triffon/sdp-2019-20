#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <algorithm>
#include <iostream>

#include "doctest.h"

#include "graph.cpp"
#include "set.h"
#include "lqueue.cpp"
#include "lstack.cpp"

unsigned simpleHashFunction(int const& x) {
  return x;
}

using TestGraph = Graph<int, simpleHashFunction>;

template <typename V>
using Path = std::vector<V>;

using TestPath = Path<int>;

template <typename K, typename V>
using LinkedHashSimple = LinkedHash<K, V, simpleHashFunction>;

template <typename V>
using VertexSet = Set<LinkedHashSimple, V>;

using TestVertexSet = VertexSet<int>;

template <typename V>
using Edge = std::pair<V, V>;

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
bool dfsPathRec(Graph<V, hashFunction>& g, V const& u, V const& v, Path<V>& path, VertexSet<V>& visited) {
  // дали вече този връх го има в пътя?
  //  if (std::find(path.begin(), path.end(), u) != path.end())
  if (visited.contains(u))
    return false;

  // няма да зациклим, добавяме го в пътя
  path.push_back(u);
  visited.insert(u);

  if (u == v)
    // намерихме път!
    return true;

  // търсим път от някой от наследниците w на u до v
  for(V w : g.successors(u))
    if (dfsPathRec(g, w, v, path, visited))
      return true;

  // от никой от наследниците на u не можем да стигнем до v
  // отказваме се от u в пътя

  path.pop_back();
  return false;
}

template <typename V>
void printPath(Path<V> const& path) {
  if (path.empty())
    return;
  for(V v : path)
    std::clog << v << " ";
  std::clog << std::endl;
}

template <typename V, HashFunction<V> hashFunction>
Path<V> dfsPath(Graph<V, hashFunction>& g, V const& u, V const& v) {
  Path<V> result;
  VertexSet<V> visited;
  if (dfsPathRec(g, u, v, result, visited)) {
    std::clog << "DFS: ";
    printPath(result);
  }
  return result;
}

template <typename V, HashFunction<V> hashFunction>
Path<V> bfsPath(Graph<V, hashFunction>& g, V const& u, V const& v) {
  Path<V> result;
  VertexSet<V> visited;
  LinkedQueue<V> queue;
  LinkedStack<Edge<V>> edges;
  // на ниво 1 е само върхът u
  queue.enqueue(u);
  visited.insert(u);
  while (!queue.empty()) {
    // вземаме поредния връх
    V current = queue.dequeue();

    // ако сме стигнали до v, връщаме пътя
    if (current == v) {
      LinkedStack<V> reversePath;
      reversePath.push(current);
      while (current != u && !edges.empty()) {
        Edge<V> e = edges.pop();
        if (e.second == current) {
          reversePath.push(e.first);
          current = e.first;
        }
      }
      while (!reversePath.empty())
        result.push_back(reversePath.pop());
      std::clog << "BFS: ";
      printPath(result);
      return result;
    }

    // маркираме непосетените наследници на current за посещаване като ги добавяме в опашката
    for(V u : g.successors(current))
      if (!visited.contains(u)) {
        queue.enqueue(u);
        visited.insert(u);
        // помним и реброто, по което сме минали
        edges.push(Edge<V>{current, u});
      }
  }
  return result;
}


template <typename V, HashFunction<V> hashFunction>
class DFSPathFinder {
public:
  static Path<V> findPath(Graph<V, hashFunction>& g, V const& u, V const& v) {
    return dfsPath(g, u, v);
  }
};

template <typename V, HashFunction<V> hashFunction>
class BFSPathFinder {
public:
  static Path<V> findPath(Graph<V, hashFunction>& g, V const& u, V const& v) {
    return bfsPath(g, u, v);
  }
};

#define TEST_BOTH DFSPathFinder<int, simpleHashFunction>, BFSPathFinder<int, simpleHashFunction>
#include "graph_problems_tests.h"
