#ifndef PAIRHASHER_H
#define PAIRHASHER_H

#include "Pair.h"
#include "Hash.h"

template <typename Key, typename Val, typename Hashfunc = Hash<Key> >
class PairHasher {
protected:
	Hashfunc hasher;
public:
	typedef Key	key_t;
	inline size_t operator ()(const Pair<Key, Val> &p) const
		{ return hasher(p.key); }
};

#endif
