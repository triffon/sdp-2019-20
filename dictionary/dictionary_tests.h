TEST_CASE("Search in an empty dictionary") {
  TestDictionary dict;
  CHECK(dict.lookup(1) == nullptr);
}

TEST_CASE("Add a single element in an empty dictionary") {
  TestDictionary dict;
  REQUIRE(dict.add(1, 10));
  int* val = dict.lookup(1);
  CHECK(val != nullptr);
  CHECK_EQ(*val, 10);
}

TEST_CASE("Remove the last element in a dictionary") {
  TestDictionary dict;
  REQUIRE(dict.add(1, 10));
  REQUIRE(dict.remove(1));
  CHECK(dict.lookup(1) == nullptr);
}

TEST_CASE("Add many elements in a dictionary and look them up") {
  TestDictionary dict;
  for (int i : {1, 3, 6, 2, 4})
    REQUIRE(dict.add(i, i * 10));

  for (int i : {6, 3, 4, 1, 2}) {
    int *val = dict.lookup(i);
    CHECK(val != nullptr);
    CHECK_EQ(*val, i * 10);
  }

  for (int i : {0, 5, 10})
    CHECK(dict.lookup(i) == nullptr);
}

TEST_CASE("Remove some added elements in a dictionary and try to look them up") {
  TestDictionary dict;
  for (int i : {1, 3, 6, 2, 4})
    REQUIRE(dict.add(i, i * 10));

  for (int i : {3, 4, 1})
    REQUIRE(dict.remove(i));

  for (int i : {1, 3, 4})
    CHECK(dict.lookup(i) == nullptr);

  for (int i : {2, 6}) {
    int *val = dict.lookup(i);
    CHECK(val != nullptr);
    CHECK_EQ(*val, i * 10);
  }
}
