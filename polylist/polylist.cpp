#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "simplequeue.cpp"
#include "simplestack.cpp"
#include "sqlist.cpp"

using TestQueue = SimpleQueue<int>;
using TestStack = SimpleStack<int>;
using TestList  = StackQueueList<int>;

#include "sqlist_tests.h"
