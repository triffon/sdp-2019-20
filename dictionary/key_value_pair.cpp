#ifndef __KEY_VALUE_PAIR_CPP
#define __KEY_VALUE_PAIR_CPP

template <typename K, typename V>
class KeyValuePair {
  K key;
  V value;

public:
  KeyValuePair(K const& k = K(), V const& v = V()) : key(k), value(v) {}

  bool operator==(KeyValuePair const& kvp) const { return key == kvp.key; }
  bool operator!=(KeyValuePair const& kvp) const { return !(*this == kvp); }
  bool operator< (KeyValuePair const& kvp) const { return key < kvp.key; }
  bool operator>=(KeyValuePair const& kvp) const { return !(*this <  kvp); }
  bool operator>(KeyValuePair const& kvp) const  { return !(*this == kvp || *this < kvp); }
  bool operator<=(KeyValuePair const& kvp) const { return !(*this >  kvp); }
};

#endif
