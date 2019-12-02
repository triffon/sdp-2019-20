#include "simplecontainer.h"
#include "llist.cpp"

//template <typename T>
//class StackQueueList : public LinkedList<SimpleContainer<T>*> {};

template <typename T>
using StackQueueList = LinkedList<SimpleContainer<T>*>;
