#ifndef PAIR_H
#define PAIR_H

template <typename Key, typename Val>
class Pair {
public:
	typedef Key	key_t;
	typedef Val	value_t;

	key_t			key;
	mutable value_t	value;

	Pair() : key(), value() {}
	Pair(const key_t &k) : key(k), value() {}
	Pair(const key_t &k, const value_t &v) : key(k), value(v) {}
	Pair(const Pair &p) : key(p.key), value(p.value) {}

	Pair &operator = (const Pair &p)
		{ value = p.value; return *this; }
	bool operator == (const Pair &p) const
		{ return key == p.key; }
	bool operator != (const Pair &p) const
		{ return key != p.key; }
	bool operator < (const Pair &p) const
		{ return key < p.key; }
};

#endif
