TEST_CASE_TEMPLATE("Add elements in a set and look them up", TestSet, TEST_SET_ALL) {
  TestSet set;
  for(int i = 1; i <= 10; i++)
    CHECK(set.insert(2 * i));

  for(int i = 1; i <= 20; i++)
    CHECK_EQ(set.contains(i), i % 2 == 0);
}
