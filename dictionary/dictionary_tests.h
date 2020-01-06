#include <fstream>

TEST_CASE_TEMPLATE("Search in an empty dictionary", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  CHECK(dict.lookup(1) == nullptr);
}

TEST_CASE_TEMPLATE("Add a single element in an empty dictionary", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  REQUIRE(dict.add(1, 10));
  int* val = dict.lookup(1);
  REQUIRE(val != nullptr);
  CHECK_EQ(*val, 10);
}

TEST_CASE_TEMPLATE("Remove the last element in a dictionary", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  REQUIRE(dict.add(1, 10));
  REQUIRE(dict.remove(1));
  CHECK(dict.lookup(1) == nullptr);
}

TEST_CASE_TEMPLATE("Add many elements in a dictionary and look them up", TestDictionary, TEST_BOTH) {
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

TEST_CASE_TEMPLATE("Remove some added elements in a dictionary and try to look them up", TestDictionary, TEST_BOTH) {
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

TEST_CASE_TEMPLATE("Enumerate keys", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  for (int i : {1, 3, 6, 2, 5, 4})
    REQUIRE(dict.add(i, i * 10));
  int i = 1;
  for(int key : dict.keys())
    CHECK(key == i++);
}

TEST_CASE_TEMPLATE("Enumerate values", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  for (int i : {1, 3, 6, 2, 5, 4})
    REQUIRE(dict.add(i, i * 10));
  int i = 10;
  for(int value : dict.values()) {
    CHECK(value == i);
    i += 10;
  }
}

TEST_CASE_TEMPLATE("Add names with phone numbers and look them up", TestStringDictionary, TEST_BOTH_STRING) {
  TestStringDictionary dict;
  std::ifstream fi("../phonebook.txt");
  std::string phone, name;
  while (fi) {
    std::getline(fi, phone, ',');
    std::getline(fi, name);
    if (fi)
      CHECK(dict.add(name, phone));
  }
  fi.close();

  fi.open("../phonebook_shuffled.txt");
  while (fi) {
    std::getline(fi, phone, ',');
    std::getline(fi, name);
    if (fi) {
      std::string* val = dict.lookup(name);
      REQUIRE(val != nullptr);
      CHECK(*val == phone);
    }
  }
}

TEST_CASE_TEMPLATE("Add names with phone numbers, remove some, and then look them up", TestStringDictionary, TEST_BOTH_STRING) {
  TestStringDictionary dict;
  std::ifstream fi("../phonebook.txt");
  std::string phone, name;
  while (fi) {
    std::getline(fi, phone, ',');
    std::getline(fi, name);
    if (fi)
      CHECK(dict.add(name, phone));
  }
  fi.close();

  // махаме от речника всички имена, започващи с 'A'
  fi.open("../phonebook.txt");
  while (fi) {
    std::getline(fi, phone, ',');
    std::getline(fi, name);
    if (fi && name[0] == 'A')
      CHECK(dict.remove(name));
  }
  fi.close();

  fi.open("../phonebook_shuffled.txt");
  while (fi) {
    std::getline(fi, phone, ',');
    std::getline(fi, name);
    if (fi) {
      std::string* val = dict.lookup(name);
      if (name[0] == 'A')
        CHECK_EQ(val, nullptr);
      else {
        REQUIRE(val != nullptr);
        CHECK(*val == phone);
      }
    }
  }
}
