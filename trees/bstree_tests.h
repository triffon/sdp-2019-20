BSTree<int> createTestBSTree() {
  BSTree<int> bst;

  bst
    .addElement("", 5)
    .addElement("L", 3)
    .addElement("R", 8)
    .addElement("LL", 2)
    .addElement("LLL", 1)
    .addElement("LR", 4)
    .addElement("RL", 6)
    .addElement("RLR", 7)
    .addElement("RR", 10);

  std::ofstream dotfile("bstree.dot");
  bst.dottyPrint(dotfile);

  return bst;
}

TEST_CASE("Test search") {
  BSTree<int> bst = createTestBSTree();

  for(int i = 1; i <= 10; i++) {
    BSTree<int>::P pos = bst.search(i);
    if (i == 9)
      CHECK(!pos);
    else {
      REQUIRE(pos);
      CHECK_EQ(*pos, i);
    }
  }
}

TEST_CASE("Test not found") {
  BSTree<int> bst = createTestBSTree();

  CHECK(!bst.search(0));
  CHECK(!bst.search(9));
  CHECK(!bst.search(11));
}
