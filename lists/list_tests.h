#define TEST_BOTH LinkedList<int>, DoubleLinkedList<int>

TEST_CASE_TEMPLATE("Insert consecutively elements at the end of the list", TestList, TEST_BOTH) {
  TestList l;
  for(int i = 1; i <= 10; i++)
    l += i;
  int i = 1;
  for(int x : l)
    CHECK_EQ(x, i++);
  CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Insert after every element in the list", TestList, TEST_BOTH) {
  TestList l;
  // вмъкваме нечетните числа от 1 до 10
  for(int i = 1; i <= 9; i += 2)
    l += i;
  // вмъкваме след всяко число
  for(typename TestList::I it = l.begin(); it; it += 2)
    l.insertAfter(it, *it + 1);

  // трябва да сме получили последователните числа от 1 до 10
  int i = 1;
  for(int x : l)
    CHECK_EQ(x, i++);
  CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Delete every even element in a list", TestList, TEST_BOTH) {
  TestList l;
  // всички числа от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;
  // изтриваме всички четни
  for(typename TestList::I it = l.begin(); it; ++it) {
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

TEST_CASE_TEMPLATE("Delete last element works correctly", TestList, TEST_BOTH) {
  TestList l;
  // всички числа от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;
  typename TestList::I it = l.begin();
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

// TODO: отрицателни тестове за deleteAfter, deleteAt и deleteBefore

TEST_CASE_TEMPLATE("Insert consecutively elements at the beginning of the list", TestList, TEST_BOTH) {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l.insertFirst(i);
  // проверка дали back е коректен
  l.insertLast(0);
  int i = 10;
  for(int x : l)
    CHECK_EQ(x, i--);
  CHECK_EQ(i, -1);
}

TEST_CASE_TEMPLATE("Insert elements before every second element in the list", TestList, TEST_BOTH) {
  TestList l;
  // четните числа от 2 до 10
  for(int i = 2; i <= 10; i += 2)
    l += i;
  // вмъкваме преди всеки елемент
  for(typename TestList::I it = l.begin(); it; ++it)
    l.insertBefore(it, *it - 1);
  // трябва да сме получили последователните числа от 1 до 10
  int i = 1;
  for(int x : l)
    CHECK_EQ(x, i++);
  CHECK_EQ(i, 11);
}

// TODO: тестове за deleteFirst и deleteLast

TEST_CASE_TEMPLATE("Delete every second element in the list", TestList, TEST_BOTH) {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;
  int i = 1;
  for(typename TestList::I it = l.begin(); it; ++it, i += 2) {
    int x;
    // не разчитаме на стойността на итератора след изтриването
    CHECK(l.deleteAt(it++, x));
    CHECK_EQ(x, i);
  }
  i = 2;
  for(int x : l) {
    CHECK_EQ(x, i);
    i += 2;
  }
  CHECK_EQ(i, 12);
}

// TODO: тест за изтриване на последния елемент от списъка, така че след това да остане празен

TEST_CASE_TEMPLATE("Delete before every second element of the list", TestList, TEST_BOTH) {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;
  int i = 1;
  // изтриваме преди всички четни числа
  for(typename TestList::I it = l.begin(); it; ++it, i += 2) {
    ++it;
    int x;
    CHECK(l.deleteBefore(it, x));
    CHECK_EQ(i, x);
  }
  // остават само четните
  i = 2;
  for(int x : l) {
    CHECK_EQ(i, x);
    i += 2;
  }
  CHECK_EQ(i, 12);
}

// TODO: тестове, че front и back остават коректно насочени след всяка операция
// например, чрез вмъкване/изтриване на елемент в началото/края

TEST_CASE_TEMPLATE("Copy initialization of lists avoids sharing", TestList, TEST_BOTH) {
  TestList l1;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l1 += i;

  TestList l2 = l1;
  l1 += 11;
  l1.insertFirst(0);

  for(int& x : l2)
    x *= 2;
  l2 += 22;
  l2.insertFirst(0);

  // в l1 са числата от 0 до 11
  int i = 0;
  for(int x : l1)
    CHECK_EQ(i++, x);
  CHECK_EQ(i, 12);

  // в l2 са четните числа от 0 до 22
  i = 0;
  for(int x : l2) {
    CHECK_EQ(i, x);
    i += 2;
  }
  CHECK_EQ(i, 24);
}

TEST_CASE_TEMPLATE("Assignment of lists avoids sharing", TestList, TEST_BOTH) {
  TestList l1, l2;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l1 += i;

  // числата от 11 до 20
  for(int i = 11; i <= 20; i++)
    l2 += i;

  l2 = l1;
  l1 += 11;
  l1.insertFirst(0);

  for(int& x : l2)
    x *= 2;
  l2 += 22;
  l2.insertFirst(0);

  // в l1 са числата от 0 до 11
  int i = 0;
  for(int x : l1)
    CHECK_EQ(i++, x);
  CHECK_EQ(i, 12);

  // в l2 са четните числа от 0 до 22
  i = 0;
  for(int x : l2) {
    CHECK_EQ(i, x);
    i += 2;
  }
  CHECK_EQ(i, 24);
}

TEST_CASE_TEMPLATE("Appending two lists", TestList, TEST_BOTH) {
  TestList l1, l2;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l1 += i;

  // числата от 11 до 20
  for(int i = 11; i <= 20; i++)
    l2 += i;

  l1.append(l2);

  // получихме числата от 1 до 20
  int i = 1;
  for(int x : l1)
    CHECK_EQ(i++, x);
  CHECK_EQ(i, 21);
}

// TODO: тестове за граничните случаи на append

TEST_CASE_TEMPLATE("Append a second list by stealing its elements", TestList, TEST_BOTH) {
  TestList l1, l2;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l1 += i;

  // числата от 11 до 20
  for(int i = 11; i <= 20; i++)
    l2 += i;

  l1.appendAssign(l2);
  CHECK(l2.empty());

  // получихме числата от 1 до 20
  int i = 1;
  for(int x : l1)
    CHECK_EQ(i++, x);
  CHECK_EQ(i, 21);
}

TEST_CASE_TEMPLATE("Reversal of non-empty list", TestList, TEST_BOTH) {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;

  reverse(l);

  int i = 10;
  for(int x : l)
    CHECK_EQ(x, i--);
  CHECK_EQ(i, 0);
}

TEST_CASE_TEMPLATE("Length works correctly", TestList, TEST_BOTH) {
  TestList l;
  for(int i = 1; i <= 10; i++) {
    CHECK_EQ(length(l), i - 1);
    l += i;
  }
  CHECK_EQ(length(l), 10);
}

TEST_CASE_TEMPLATE("Split list of even length", TestList, TEST_BOTH) {
  TestList l, l1, l2;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;

  split(l, l1, l2);

  // TODO: да се провери, че множествата на елементите на l1 и l2 общо правят
  // множеството от елементите на l
  CHECK_EQ(length(l1), length(l2));
  CHECK_EQ(length(l1) + length(l2), length(l));
}

TEST_CASE_TEMPLATE("Split list of odd length", TestList, TEST_BOTH) {
  TestList l, l1, l2;
  // числата от 1 до 11
  for(int i = 1; i <= 11; i++)
    l += i;

  split(l, l1, l2);

  // TODO: да се провери, че множествата на елементите на l1 и l2 общо правят
  // множеството от елементите на l
  CHECK_EQ(std::abs((int)length(l1) - (int)length(l2)), 1);
  CHECK_EQ(length(l1) + length(l2), length(l));
}

TEST_CASE_TEMPLATE("Merge two lists", TestList, TEST_BOTH) {
  TestList l1, l2;
  for(int x : {1, 3, 6, 8})
    l1.insertLast(x);
  for(int x : {2, 4, 5, 7, 9, 10})
    l2.insertLast(x);

  TestList l = merge(l1, l2);

  // получихме числата от 1 до 10
  int i = 1;
  for(int x : l)
    CHECK_EQ(i++, x);
  CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Merge sort a list", TestList, TEST_BOTH) {
  TestList l;
  for(int x : { 5, 2, 7, 1, 10, 3, 6, 8, 4, 9})
    l.insertLast(x);

  TestList result = mergeSort(l);

  // получихме числата от 1 до 10
  int i = 1;
  for(int x : result)
    CHECK_EQ(i++, x);
  CHECK_EQ(i, 11);  
}

int plus(const int& x, const int& y) { return x + y; }

TEST_CASE_TEMPLATE("Sum list elements with foldr", TestList, TEST_BOTH) {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;

  //  CHECK_EQ(foldr(plus, 0, l.begin()), 55);
  CHECK_EQ(foldr<typename TestList::I, int>([](int const& x, int const& y) { return x + y; }, 0, l.begin()), 55);
}

TEST_CASE_TEMPLATE("Sum list elements with foldl", TestList, TEST_BOTH) {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;

  CHECK_EQ(foldl(plus, 0, l.begin()), 55);
}

int square(int const& x) { return x * x; }

TEST_CASE_TEMPLATE("Map list with square", TestList, TEST_BOTH) {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;

  //  TestList result = map(square, l);
  TestList result = map<TestList, int>([](int const& x) { return x * x; }, l);

  // получихме квадратите на числата от 1 до 10
  int i = 1;
  for(int x : result)
    CHECK_EQ(square(i++), x);
  CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Destrucive map list with square", TestList, TEST_BOTH) {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;

  mapd(square, l);

  // получихме квадратите на числата от 1 до 10
  int i = 1;
  for(int x : l)
    CHECK_EQ(square(i++), x);
  CHECK_EQ(i, 11);
}

bool even(int const& x) { return x % 2 == 0; }
bool odd (int const& x) { return x % 2 != 0; }

TEST_CASE_TEMPLATE("Filter only even elements in a list", TestList, TEST_BOTH) {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;

  //  TestList result = filter(even, l);
  TestList result = filter<TestList, int>([](int const& x) { return x % 2 == 0; }, l);

  // получихме четните числа от 1 до 10
  int i = 2;
  for(int x : result) {
    CHECK_EQ(i, x);
    i += 2;
  }
  CHECK_EQ(i, 12);
}

TEST_CASE_TEMPLATE("Sum odd squares in a list", TestList, TEST_BOTH) {
  TestList l;
  // числата от 1 до 5
  for(int i = 1; i <= 5; i++)
    l += i;

  CHECK_EQ(foldr(plus, 0, map(square, filter(odd, l)).begin()), 35);
}
