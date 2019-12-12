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

  bst.dottyPrint("bstree.dot");
}

TEST_CASE("Test search") {
  BSTree<int> bst = createTestBSTree();
}
