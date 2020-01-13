#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "graph.cpp"

unsigned simpleHashFunction(int const& x) {
  return x;
}

using TestGraph = Graph<int, simpleHashFunction>;

#include "graph_tests.h"
