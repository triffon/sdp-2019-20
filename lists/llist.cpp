template <typename T, typename P>
class LinkedList {
public:

  LinkedList();

  LinkedList(LinkedList const& ll);
  LinkedList& operator=(LinkedList const& ll);
  ~LinkedList();

  bool empty() const;

  bool insertBefore(T const& x, P const& p);
  bool insertAfter (T const& x, P const& p);

  bool deleteBefore(P const& p);
  bool deleteAt    (P const& p);
  bool deleteAfter (P const& p);

  bool deleteBefore(P const& p, T& x);
  bool deleteAt    (P const& p, T& x);
  bool deleteAfter (P const& p, T& x);

  T const& getAt(P const& p) const;
  T&       getAt(P const& p);
};
