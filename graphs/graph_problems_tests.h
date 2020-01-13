#include "tests_helpers.h"

TEST_CASE("All vertices in an empty graph are childless") {
  const int N = 6;
  TestGraph g = createEmptyGraph(N);
  std::vector<int> result;
  for(int i = 1; i <= N; i++)
    result.push_back(i);
  CHECK(result == childless(g)); 
}

TEST_CASE("One vertex in a sample graph is childless") {
  TestGraph g = createTestGraph();
  std::vector<int> result = childless(g);
  CHECK(result.size() == 1);
  CHECK(result[0] == 4);
}

TEST_CASE("No vertices in a full graph are childless") {
  TestGraph g = createFullGraph(6);
  CHECK(childless(g).empty());
}

TEST_CASE("Empty graph is symmetric") {
  TestGraph g = createEmptyGraph(6);
  CHECK(isSymmetric(g));
}

TEST_CASE("Full graph is symmetric") {
  TestGraph g = createFullGraph(6);
  CHECK(isSymmetric(g));
}

TEST_CASE("Sample graph is not symmetric") {
  TestGraph g = createTestGraph();
  CHECK(!isSymmetric(g));
}

TEST_CASE("Simple graph is symmetric") {
  TestGraph g = createEmptyGraph(3);
  CHECK(isSymmetric(g));
  g.addEdge(1, 3);
  CHECK(!isSymmetric(g));
  g.addEdge(3, 1);
  CHECK(isSymmetric(g));
  g.addEdge(1, 2);
  CHECK(!isSymmetric(g));
  g.addEdge(2, 1);
  CHECK(isSymmetric(g));
}

TEST_CASE_TEMPLATE("No path in empty graph", PathFinder, TEST_BOTH) {
  int const N = 6;
  TestGraph g = createEmptyGraph(N);
  for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++)
      if (i != j)
        CHECK(PathFinder::findPath(g, i, j).empty());
}

TEST_CASE_TEMPLATE("Path between every two vertices in a full graph", PathFinder, TEST_BOTH) {
  int const N = 6;
  TestGraph g = createFullGraph(N);
  for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++)
      if (i != j)
        CHECK(isPath(g, PathFinder::findPath(g, i, j), i, j));
}

TEST_CASE_TEMPLATE("No path to an isolated vertex", PathFinder, TEST_BOTH) {
  int const N = 16;
  std::clog << "start: No path to an isolated vertex\n";
  TestGraph g = createFullGraph(N);
  g.addVertex(N + 1);
  CHECK(PathFinder::findPath(g, 1, N + 1).empty());
  std::clog << "end: No path to an isolated vertex\n";
}

TEST_CASE_TEMPLATE("Paths in the sample graph", PathFinder, TEST_BOTH) {
  TestGraph g = createTestGraph();
  for(int i = 2; i <= 6; i++)
    CHECK(isPath(g, PathFinder::findPath(g, 1, i), 1, i));

  for(int i = 2; i <= 6; i++)
    CHECK(PathFinder::findPath(g, i, 1).empty());

  for(int i = 1; i <= 6; i++)
    if (i != 4)
      CHECK(PathFinder::findPath(g, 4, i).empty());

  for(int i : {2, 3, 5, 6})
    for(int j = 1; j <= 6; j++)
      if (i != j && j != 1)
        CHECK(isPath(g, PathFinder::findPath(g, i, j), i, j));
}
