SList* createTestList() {
  return
    (new SList)
    ->add((new SList)
          ->add(new SInt(1))
          ->add((new SList)
                ->add(new SInt(2))))
    ->add((new SList)
          ->add((new SList)
                ->add((new SList)
                      ->add(new SInt(3)))
                ->add(new SInt(4)))
          ->add((new SList)
                ->add(new SInt(5))
                ->add((new SList)
                      ->add(new SInt(6))))
          ->add(new SList)
          ->add((new SList)
                ->add(new SInt(7))))
    ->add(new SInt(8));
}

#include <sstream>

TEST_CASE("Printing of test list") {
  SList* sl = createTestList();
  std::ostringstream oss;
  sl->print(oss);
  CHECK_EQ(oss.str(), "((1 (2)) (((3) 4) (5 (6)) () (7)) 8)");
  delete sl;
}

TEST_CASE("Collecting of elements of test list") {
  SList* sl = createTestList();
  LinkedList<int> l;
  sl->collect(l);
  int i = 1;

  for(int x : l)
    CHECK_EQ(x, i++);
  CHECK_EQ(i, 9);

  delete sl;
}
