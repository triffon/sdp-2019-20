#ifndef __GRAPH_CPP
#define __GRAPH_CPP

#include <vector>
#include "linked_hash.cpp"

template <typename V, HashFunction<V> hashFunction>
class Graph {
  using VertexList = LinkedList<V>;
  using SuccList = LinkedHash<V, VertexList, hashFunction>;
  
  SuccList graph;
  VertexList emptyVertexList;

public:
  std::vector<V> vertices() {
    return graph.keys();
  }

  VertexList const& successors(V const& v) const {
    VertexList const* succs = graph.lookupConst(v);
    if (succs == nullptr)
      return emptyVertexList;

    return *succs;
  }

  bool addVertex(V const& v) {
    return graph.add(v, emptyVertexList);
  }

  bool removeVertex(V const& v) {
    // първо махаме ребрата към v
    for(int u : vertices())
      removeEdge(u, v);

    return graph.remove(v);
  }

  bool isEdge(V const& u, V const& v) {
    VertexList* succs = graph.lookup(u);
    if (succs == nullptr)
      return false;
    for(int w : *succs)
      if (w == v)
        return true;
    return false;
  }

  bool addEdge(V const& u, V const& v) {
    VertexList* succs = graph.lookup(u);
    if (succs == nullptr)
      return false;
    // искаме да го няма вече в наследниците
    if (isEdge(u, v))
      return false;
    succs->insertLast(v);
    return true;
  }

  bool removeEdge(V const& u, V const& v) {
    VertexList* succs = graph.lookup(u);
    if (succs == nullptr)
      return false;
    for(typename VertexList::I it = succs->begin(); it; ++it)
      if (*it == v) {
        succs->deleteAt(it);
        return true;
      }
    return false;
  }
};

#endif
