#ifndef __TESTS_HELPERS
#define __TESTS_HELPERS

TestGraph createEmptyGraph(int n) {
  TestGraph g;
  for(int i = 1; i <= n; i++)
    g.addVertex(i);
  return g;
}

TestGraph createTestGraph() {
  TestGraph g = createEmptyGraph(6);
  std::vector<std::pair<int, int>> v = {{1, 2}, {1, 3}, {2, 3}, {3, 4}, {3, 5}, {5, 4}, {5, 2}, {6, 2}, {5, 6}};
  for(auto p : v)
    g.addEdge(p.first, p.second);
  return g;
}

TestGraph createFullGraph(int n) {
  TestGraph g = createEmptyGraph(n);
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
      g.addEdge(i, j);
  return g;
}

#endif
