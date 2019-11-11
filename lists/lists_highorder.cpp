template <typename T>
using UnaryOperation  = T (*)(T const&);

template <typename T>
using BinaryOperation = T (*)(T const&, T const&);

template <typename T>
using Predicate = bool (*)(T const&);

// свиване надясно
template <typename I, typename T = typename I::Type>
T foldr(BinaryOperation<T> op, T nv, I const& it) {
  if (!it)
    return nv;
  return op(it.getConst(), foldr(op, nv, it.next()));
}

template <typename I, typename T = typename I::Type>
T foldl(BinaryOperation<T> op, T nv, I it) {
  while (it)
    nv = op(nv, *it++);
  return nv;
}

template <typename List, typename T = typename List::Type>
List map(UnaryOperation<T> f, List const& l) {
  List result;
  for(T const& x : l)
    result.insertLast(f(x));
  return result;
}

template <typename List, typename T = typename List::Type>
void mapd(UnaryOperation<T> f, List& l) {
  for(T& x : l)
    x = f(x);
}

template <typename List, typename T = typename List::Type>
List filter(Predicate<T> p, List const& l) {
  List result;
  for(T const& x : l)
    if (p(x))
      result.insertLast(x);
  return result;
}
