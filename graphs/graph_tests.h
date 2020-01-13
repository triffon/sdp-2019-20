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

TEST_CASE("All vertices in a full graph") {
  const int N = 3;
  TestGraph g = createFullGraph(N);

  std::vector<int> v = g.vertices(), v2;
  // TODO: да се подобри сравнението на вектори да допуска разбъркан ред на върховете
  for(int i = 1; i <= N; i++)
    v2.push_back(i);
  CHECK_EQ(v, v2);
}


TEST_CASE("No edges in an empty graph") {
  const int N = 3;
  TestGraph g = createEmptyGraph(N);
  
  for(int i = 1; i <= N; i++) {
    // искаме да няма наследници
    CHECK(g.successors(i).empty());
    for(int j = 1; j <= N; j++)
      CHECK(!g.isEdge(i, j));
  }
}

TEST_CASE("One edge in a one-edged graph") {
  const int N = 3;
  TestGraph g = createEmptyGraph(N);
  CHECK(g.addEdge(1, 2));

  for(int v : g.successors(1))
    CHECK_EQ(v, 2);
  
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

  for(int v : g.successors(1))
    CHECK((v == 2 || v == 3));

  for(int v : g.successors(3))
    CHECK((v == 4 || v == 5));

  for(int v : g.successors(5))
    CHECK((v == 4 || v == 2 || v == 6));
}

TEST_CASE("Check edges in a full graph") {
  const int N = 6;
  TestGraph g = createFullGraph(N);

  for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++)
      CHECK(g.isEdge(i, j));

  for(int i = 1; i <= N; i++)
    for(int j : g.successors(i))
      CHECK((1 <= j && j <= N));
}

TEST_CASE("Remove vertex correctly removes vertex from an empty graph") {
  const int N = 6;
  TestGraph g = createEmptyGraph(N);

  CHECK(!g.removeVertex(N+10));
  CHECK(g.removeVertex(3));

  for(int i : g.vertices())
    CHECK((1 <= i && i <= 6 && i != 3));

  CHECK(!g.removeVertex(3));
}

TEST_CASE("Remove vertex correctly removes vertex from a simple graph") {
  TestGraph g = createTestGraph();

  CHECK(g.removeVertex(2));

  CHECK(!g.isEdge(2, 3));
  CHECK(!g.isEdge(1, 2));
  CHECK(!g.isEdge(5, 2));
  CHECK(!g.isEdge(6, 2));

  CHECK(g.successors(2).empty());

  CHECK(!g.removeVertex(2));
}

TEST_CASE("Remove vertex correctly removes vertex from a full graph") {
  const int N = 6;
  TestGraph g = createFullGraph(N);

  CHECK(g.removeVertex(2));

  for(int i = 1; i <= 6; i++)
    CHECK((!g.isEdge(2, i) && !g.isEdge(i, 2)));

  CHECK(g.successors(2).empty());

  CHECK(!g.removeVertex(2));
}

TEST_CASE("Remove edge from an empty graph is unsuccessful") {
  const int N = 6;
  TestGraph g = createEmptyGraph(N);

  for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++)
      CHECK(!g.removeEdge(i, j));
}

TEST_CASE("Remove edge from a simple graph is successful") {
  TestGraph g = createTestGraph();

  CHECK(!g.removeEdge(6, 3));
  CHECK(g.removeEdge(5, 4));
  CHECK(!g.isEdge(5, 4));
  CHECK(!g.removeEdge(5, 4));
}

TEST_CASE("Remove all edges from a full graph is successful") {
  const int N = 6;
  TestGraph g = createFullGraph(N);

  for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++)
      CHECK(g.removeEdge(i, j));

  for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++) {
      CHECK(!g.isEdge(i, j));
      CHECK(!g.removeEdge(i, j));
    }
}
