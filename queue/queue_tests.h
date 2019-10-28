#include <set>

TEST_CASE("Default constructor creates empty queue") {
  TestQueue q;
  CHECK(q.empty());
}

TEST_CASE("Enqueueing an element creates a non-empty queue") {
  TestQueue q;
  CHECK(q.enqueue(42));
  CHECK(!q.empty());
}

TEST_CASE("Enqueueing elements after the first one does not change head of queue") {
  TestQueue q;
  const int N = 10;
  for(int i = 0; i < N; i++)
    CHECK(q.enqueue(i));
  CHECK_EQ(q.head(), 0);
}

TEST_CASE("Dequeueing the first element removes only it and does not change the others") {
  TestQueue q;
  const int N = 10;
  for(int i = 0; i < N; i++)
    CHECK(q.enqueue(i));
  CHECK_EQ(q.dequeue(), 0);
  for(int i = 1; i < N; i++) {
    CHECK(!q.empty());
    CHECK_EQ(q.dequeue(), i);
  }
  CHECK(q.empty());
}

TEST_CASE("Multiple dequeues after enqueues should work") {
  TestQueue q;
  const int N = 150;
  const int THE_ANSWER = 42;
  for(int i = 0; i < N; i++) {
    CHECK(q.enqueue(THE_ANSWER));
    CHECK_EQ(q.dequeue(), THE_ANSWER);
  }
  CHECK(q.empty());
}

TEST_CASE("Minqueue correctly extracts the minimal element in a queue with elements in no particular order") {
  TestQueue q;
  std::set<int> s = {5, 3, 6, 1, 2};
  for (int x : s)
    q.enqueue(x);
  int min = minQueue(q, 0);
  CHECK_EQ(min, 1);
  s.erase(s.find(min));
  while (!q.empty()) {
    std::set<int>::iterator it = s.find(q.dequeue());
    CHECK(it != s.end());
    s.erase(it);
  }
  CHECK(s.empty());
}

TEST_CASE("sortQueue correctly sorts a queue with elements in no particular order") {
  TestQueue q;
  for(int x : { 5, 8, 9, 7, 4, 2, 1, 6, 10, 3 })
    q.enqueue(x);
  TestQueue r;
  sortQueue(q, r, 0);
  for(int i = 1; i <= 10; i++)
    CHECK_EQ(r.dequeue(), i);
  CHECK(r.empty());
}
