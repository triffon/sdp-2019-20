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
