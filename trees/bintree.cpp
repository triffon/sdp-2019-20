#ifndef __BINTREE_CPP
#define __BINTREE_CPP

#include <cstring>
#include <cassert>
#include <iostream>
#include <iomanip>

template <class T>
struct BinTreeNode
{
  T data;
  BinTreeNode *left, *right;

  BinTreeNode (const T&, BinTreeNode*, BinTreeNode*);
  BinTreeNode ();
};

template <typename T>
class BinTreePosition {
  using BTN = BinTreeNode<T>;
  using P = BinTreePosition<T>;
  BTN* ptr;

public:
  BinTreePosition(BTN* _ptr = nullptr) : ptr(_ptr) {}

  bool valid() const { return ptr != nullptr; }

  P left() const {
    if (!valid())
      return P();    
    return P(ptr->left);
  }

  P right() const {
    if (!valid())
      return P();    
    return P(ptr->right);
  }

  T const& get() const { return ptr->data; }
  T&       get()       { return ptr->data; }

  // pos <-> pos.valid();
  operator bool() const { return valid(); }

  // ++pos
  P& operator++() {
    return (*this = right());
  }

  // pos++
  P operator++(int) {
    P save = *this;
    ++(*this);
    return save;
  }

  // --pos
  P& operator--() {
    return (*this = left());
  }

  // pos--
  P operator--(int) {
    P save = *this;
    --(*this);
    return save;
  }

  // *pos = 3;
  T& operator*() { return get(); }

  bool operator==(P const& pos) const { return ptr == pos.ptr; }
  bool operator!=(P const& pos) const { return !(*this == pos); }

  P operator-() const { return left(); }
  P operator+() const { return right(); }
};

template <class T>
class BinTree
{

public:

  using P = BinTreePosition<T>;
  
  BinTree ();
  BinTree (const T&);
  //        BinTree (const T&, const BinTree<T>&, const BinTree<T>&);

  P rootPos() const { return P(root); }
  operator P() const { return rootPos(); } 

  BinTree<T>& addElement (const char*, const T&);

  void printTree (std::ostream&);
  void prettyPrint (std::ostream&);
  void dottyPrint (std::ostream&);

  bool member (const T& x);
  T sum ();

  T reduce (T (*op)(const T&, const T&), const T& null_val);

private:
  BinTreeNode<T> *root;

  void printTreeHelp (std::ostream&, BinTreeNode<T> *current);
  void prettyPrintHelp (std::ostream&, BinTreeNode<T> *current, int level);
  void dottyPrintHelp (std::ostream&, BinTreeNode<T> *current);

  bool memberHelp (const T& x, BinTreeNode<T> *current);
  T sumHelp (BinTreeNode<T> *current);

  T reduceHelp (T (*op)(const T&, const T&), const T& null_val, BinTreeNode<T> *current);


};

template <class T>
BinTreeNode<T>::BinTreeNode (const T& _data, BinTreeNode<T>* _left, BinTreeNode<T>* _right):data(_data),left(_left),right(_right){}

template <class T>
BinTreeNode<T>::BinTreeNode ()
{}


template <class T>
BinTree<T>::BinTree ()
{
  root = nullptr;
}

template <class T>
BinTree<T>::BinTree (const T &x)
{
  root = new BinTreeNode<T> (x,nullptr,nullptr);
}

/*template <class T>
  BinTree<T>::BinTree (const T &x, const BinTree<T> &l, const BinTree<T> &r)
  {
  root = new BinTreeNode<T> (x,l.root, r.root);
  }*/

template <class T>
BinTree<T>& BinTree<T>::addElement (const char* trace, const T& x)
{
  if (strlen(trace) == 0)
    {
      assert (root == nullptr);
      root = new BinTreeNode<T> (x,nullptr,nullptr);
      return *this;
    }

  assert (root != nullptr);
  BinTreeNode<T> *current = root;

  for (int i = 0; i < strlen (trace)-1; i++)
    {
      assert (trace[i] == 'L' || trace[i] == 'R');
      if (trace[i] == 'L')
        {
          current = current->left;
        } else {
        current = current->right;
      }
      assert (current != nullptr);
    }
  //current е родителя на новия елемент
  assert (trace[strlen(trace)-1] == 'L' || trace[strlen(trace)-1] == 'R');
  if (trace[strlen(trace)-1]=='L')
    {
      assert (current->left == nullptr);
      current->left = new BinTreeNode<T> (x,nullptr,nullptr);
    } else {
    assert (current->right == nullptr);
    current->right = new BinTreeNode<T> (x,nullptr,nullptr);
  }

  return *this;

}

template <class T>
void BinTree<T>::printTree (std::ostream& out)
{
  printTreeHelp (out, root);
}

template <class T>
void BinTree<T>::printTreeHelp (std::ostream& out, BinTreeNode<T> *current)
{
  if (current == nullptr)
    {
      return;
    }

  printTreeHelp (out,current->left);
  out << current->data << " ";
  printTreeHelp (out,current->right);

}

template <class T>
void BinTree<T>::prettyPrint (std::ostream& out)
{
  prettyPrintHelp (out, root, 0);
}

template <class T>
void BinTree<T>::prettyPrintHelp (std::ostream& out, BinTreeNode<T> *current, int level)
{
  if (current == nullptr)
    {
      return;
    }

  prettyPrintHelp (out, current->right,level+1);
  out << std::setw(level*2) << " " << current->data << std::endl;
  prettyPrintHelp (out, current->left, level+1);

}


template <class T>
void BinTree<T>::dottyPrint (std::ostream& out)
{
  out << "digraph G {" << std::endl;
  dottyPrintHelp (out, root);
  out << "}";
}

template <class T>
void BinTree<T>::dottyPrintHelp (std::ostream& out, BinTreeNode<T> *current)
{

  if (current == nullptr)
    {
      return;
    }

  if (current->left != nullptr)
    {
      out << (long)current << "->" << (long)current->left << "[color=\"red\"];" << std::endl;
    }
  if (current->right != nullptr)
    {
      out << (long)current << "->" << (long)current->right << "[color=\"green\"];" << std::endl;
    }


  out << (long)current << "[label=\"" << current->data << "\"];" << std::endl;

  dottyPrintHelp (out, current->right);
  dottyPrintHelp (out, current->left);

}

template <class T>
bool BinTree<T>::member (const T& x)
{
  return memberHelp (x,root);
}

template <class T>
bool BinTree<T>::memberHelp (const T& x, BinTreeNode<T> *current)
{
  if (current == nullptr)
    {
      return false;
    }

  return current->data == x ||
    memberHelp (x,current->left) ||
    memberHelp (x,current->right);
}

template <class T>
T BinTree<T>::sum ()
{
  return sumHelp (root);
}

template <class T>
T BinTree<T>::sumHelp (BinTreeNode<T> *current)
{
  if (current == nullptr)
    {
      return 0;
    }

  return current->data +
    sumHelp (current->left) +
    sumHelp (current->right);
}

template <class T>
T BinTree<T>::reduce (T (*op)(const T&, const T&), const T& null_val)
{
  return reduceHelp (op,null_val, root);
}

template <class T>
T BinTree<T>::reduceHelp (T (*op)(const T&, const T&), const T& null_val, BinTreeNode<T> *current)
{
  if (current == nullptr)
    {
      return null_val;
    }

  return op (current->data,
             op (reduceHelp (op,null_val,current->left),
                 reduceHelp (op,null_val,current->right)));
}

template <typename T>
unsigned depth(BinTreePosition<T> p) {
  if (!p)
    return 0;
  return 1 + std::max(depth(-p), depth(+p));
}

#endif
