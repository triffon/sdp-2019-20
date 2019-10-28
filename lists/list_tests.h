TEST_CASE("Insert consecutively elements at the end of the list") {
  TestList l;
  for(int i = 1; i <= 10; i++)
    CHECK(l.insertLast(i));
  int i;
  TestList::I it;
  for(it = l.begin(), i = 1; it; ++it, ++i)
    CHECK_EQ(*it, i);
  CHECK_EQ(i, 11);
}
