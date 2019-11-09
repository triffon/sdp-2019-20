TEST_CASE("Insert consecutively elements at the end of the list") {
  TestList l;
  for(int i = 1; i <= 10; i++)
    l += i;
  int i = 1;
  for(int x : l)
    CHECK_EQ(x, i++);
  CHECK_EQ(i, 11);
}
