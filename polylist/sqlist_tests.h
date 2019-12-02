TEST_CASE("New elements are added correcly") {
  TestList l;
  TestQueue q;
  TestStack s;
  l += &q;
  l += &s;

  for(int i = 1; i <= 10; i++)
    for(SimpleContainer<int>* sc : l)
      CHECK(sc->insert(i));

  for(int i = 1; i <= 10; i++)
    CHECK_EQ(q.dequeue(), i);

  for(int i = 10; i >= 1; i--)
    CHECK_EQ(s.pop(), i);
  
  CHECK(q.empty());
  CHECK(s.empty());
}

TEST_CASE("Elements are removed correctly") {
  TestList l;
  TestQueue q;
  TestStack s;
  l += &q;
  l += &s;

  for(int i = 1; i <= 10; i++)
    q.enqueue(i);

  for(int i = 10; i >= 1; i--)
    s.push(i);

  for(int i = 1; i <= 10; i++)
    for(SimpleContainer<int>* sc : l) {
      int x;
      CHECK(sc->remove(x));
      CHECK_EQ(x, i);
    }
}
