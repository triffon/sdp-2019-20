#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "llist.cpp"
#include "dllist.cpp"

// обръща реда на елементите в даден списък
// не зависи от реализацията на списъка
// O(n) по време и O(n) по памет
template <typename List>
void reverse(List& l) {
  typename List::I it = l.begin();
  typename List::Type x;
  while (l.deleteAfter(it, x))
    l.insertFirst(x);
}

// дължина на списък
// O(n) по време и O(1) по памет
template <typename List>
unsigned length(List const& l) {
  unsigned result = 0;
  for(typename List::I it = l.begin(); it; ++it)
    ++result;
  return result;
}

// разделя елементите на l в списъците l1 и l2 приблизително по равно
// O(n) по време и O(n) по памет
template <typename List>
void split(List const& l, List& l1, List& l2) {
  List *me = &l1, *you = &l2;
  for(typename List::Type x : l) {
    me->insertLast(x);
    std::swap(me, you);
  }
}

// слива два списъка подредени във възходящ ред
// O(n+m) по време и O(n+m) по памет
template <typename List>
List merge(List const& l1, List const& l2) {
  List result;
  typename List::I it1 = l1.begin(), it2 = l2.begin();

  while (it1 && it2)
    if (*it1 < *it2)
      result.insertLast(*it1++);
    else
      result.insertLast(*it2++);

  // !it1 || !it2
  while (it1)
    result.insertLast(*it1++);
  while (it2)
    result.insertLast(*it2++);
    
  return result;
}

// O(n.log(n)) по време и O(n.log(n)) по памет
template <typename List>
List mergeSort(List const& l) {
  // 0. дъно
  if (length(l) <= 1)
    return l;

  // 1. разделяме списъка поравно
  List l1, l2;
  split(l, l1, l2);

  // 2. сортираме рекурсивно двата списъка
  // 3. сливаме резултатите
  return merge(mergeSort(l1), mergeSort(l2));
}

#include "lists_highorder.cpp"

template <typename T>
bool isPalindrome(DoubleLinkedList<T> const& dl) {
  typename DoubleLinkedList<T>::I fit = dl.begin(), bit = dl.last();
  if (dl.empty())
    return true;
  while (fit != bit && fit.prev() != bit && *fit++ == *bit--);
  return fit == bit || fit.prev() == bit;
  // *fit != *bit --> намерили сме различни елементи
  // fit == bit   --> итераторите са се срещнали
  // fit.prev() == bit --> итераторите са се разминали 
}

#include "list_tests.h"

