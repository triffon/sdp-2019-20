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
