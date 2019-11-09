TEST_CASE("Insert consecutively elements at the end of the list") {
  TestList l;
  for(int i = 1; i <= 10; i++)
    l += i;
  int i = 1;
  for(int x : l)
    CHECK_EQ(x, i++);
  CHECK_EQ(i, 11);
}

TEST_CASE("Insert after every element in the list") {
  TestList l;
  // вмъкваме нечетните числа от 1 до 10
  for(int i = 1; i <= 9; i += 2)
    l += i;
  // вмъкваме след всяко число
  for(TestList::I it = l.begin(); it; it += 2)
    l.insertAfter(it, *it + 1);

  // трябва да сме получили последователните числа от 1 до 10
  int i = 1;
  for(int x : l)
    CHECK_EQ(x, i++);
  CHECK_EQ(i, 11);
}

TEST_CASE("Delete every even element in a list") {
  TestList l;
  // всички числа от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;
  // изтриваме всички четни
  for(TestList::I it = l.begin(); it; ++it) {
    int x;
    CHECK(l.deleteAfter(it, x));
    CHECK_EQ(x, *it + 1);
  }
  // проверяваме дали са останали само нечетните числа
  int i = 1;
  for(int x : l) {
    CHECK_EQ(x, i);
    i += 2;
  }
  CHECK_EQ(i, 11);
}

TEST_CASE("Delete last element works correctly") {
  TestList l;
  // всички числа от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;
  TestList::I it = l.begin();
  it += 8;
  // върху предпоследния елемент сме
  int x;
  CHECK(l.deleteAfter(it, x));
  CHECK_EQ(x, 10);
  l += 11;
  // искаме да проверим дали последният елемент наистина е 11?
  it = l.begin();
  CHECK_EQ(*(it += 9), 11);
}

// TODO: отрицателни тестове за deleteAfter
