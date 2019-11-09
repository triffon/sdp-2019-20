#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "llist.cpp"

using TestList = LinkedList<int>;

// обръща реда на елементите в даден списък
// не зависи от реализацията на списъка
template <typename List>
void reverse(List& l) {
  typename List::I it = l.begin();
  typename List::Type x;
  while (l.deleteAfter(it, x))
    l.insertFirst(x);
}

#include "list_tests.h"
