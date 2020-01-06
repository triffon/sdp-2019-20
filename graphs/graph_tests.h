TestGraph createTestGraph() {
  TestGraph g;
  for(int i = 1; i <= 6; i++)
    g.addVertex(i);
  for(std::pair<int, int> p : {{1, 2}, {1, 3}, {2, 3}, {3, 4}, {3, 5}, {5, 4}, {5, 2}, {6, 2}, {5, 6}})
    g.addEdge(p.first, p.second);
  return g;
}

TestGraph createEmptyGraph(int n) {
  TestGraph g;
  for(int i = 1; i <= n; i++)
    g.addVertex(i);
  return g;
}

TestGraph createFullGraph(int n) {
  TestGraph g = createEmptyGraph();
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
      g.addEdge(i, j);
  return g;
}

TEST_CASE("All vertices in a full graph") {
  const int N = 3;
  TestGraph g = createFullGraph(N);

  std::vector<int> v = g.vertices(), v2;
  for(int i = 1; i <= N; i++)
    v2.push_back(i);
  CHECK_EQ(v, v2);
}


TEST_CASE("No edges in an empty graph") {
  const int N = 3;
  TestGraph g = createEmptyGraph(N);
  
  for(int i = 1; i <= N; i++) {
    // искаме да няма наследници
    CHECK(!g.successors(i));
    for(int j = 1; j <= N; j++)
      CHECK(!g.isEdge(i, j));
  }
}

TEST_CASE("One edge in a one-edged graph") {
  const int N = 3;
  TestGraph g = createEmptyGraph(N);
  CHECK(g.addEdge(1, 2));

  for(TestGraph::I it = g.successor(1); it; ++it)
    CHECK_EQ(*it, 2);
  
  for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++)
      CHECK_EQ(g.isEdge(i, j), i == 1 && j == 2);
}

TEST_CASE("Check edges in a simple graph") {
  TestGraph g = createTestGraph();

  CHECK(g.isEdge(1, 2));
  CHECK(g.isEdge(1, 3));
  CHECK(g.isEdge(2, 3));
  CHECK(g.isEdge(3, 4));
  CHECK(g.isEdge(3, 5));
  CHECK(g.isEdge(5, 4));
  CHECK(g.isEdge(5, 2));
  CHECK(g.isEdge(6, 2));
  CHECK(g.isEdge(5, 6));
}
