#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "squeue.cpp"
#include "lqueue.cpp"

// using TestQueue = StaticQueue<int>;
using TestQueue = LinkedQueue<int>;

#include "queue_tests.h"
