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

// TODO: отрицателни тестове за deleteAfter, deleteAt и deleteBefore

TEST_CASE("Insert consecutively elements at the beginning of the list") {
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

TEST_CASE("Insert elements before every second element in the list") {
  TestList l;
  // четните числа от 2 до 10
  for(int i = 2; i <= 10; i += 2)
    l += i;
  // вмъкваме преди всеки елемент
  for(TestList::I it = l.begin(); it; ++it)
    l.insertBefore(it, *it - 1);
  // трябва да сме получили последователните числа от 1 до 10
  int i = 1;
  for(int x : l)
    CHECK_EQ(x, i++);
  CHECK_EQ(i, 11);
}

// TODO: тестове за deleteFirst и deleteLast

TEST_CASE("Delete every second element in the list") {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;
  int i = 1;
  for(TestList::I it = l.begin(); it; ++it, i += 2) {
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

TEST_CASE("Delete before every second element of the list") {
  TestList l;
  // числата от 1 до 10
  for(int i = 1; i <= 10; i++)
    l += i;
  int i = 1;
  // изтриваме преди всички четни числа
  for(TestList::I it = l.begin(); it; ++it, i += 2) {
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

TEST_CASE("Copy initialization of lists avoids sharing") {
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

TEST_CASE("Assignment of lists avoids sharing") {
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

TEST_CASE("Appending two lists") {
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

TEST_CASE("Append a second list by stealing its elements") {
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

TEST_CASE("Reversal of non-empty list") {
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
