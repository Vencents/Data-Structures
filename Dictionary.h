#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "BinarySearchTree.h"
#include "Pair.h"

/*
 * BinarySearchTree implements Dictionary by default.
 * If you want to use the hashtable, use:
 * Dictionary<Key, Val, Hashtable< Pair<Key, Val>, PairHasher<Key, Val> > >
 */

template <
	typename Key,
	typename Val,
	typename Container = BinarySearchTree<Pair<Key, Val> > >
class Dictionary {
public:
	typedef Key		key_t;
	typedef Val		value_t;
	typedef typename Container::Iterator Iterator;
protected:
	typedef Pair<Key, Val>	pair_t;
	Container c;
public:
	Dictionary() : c() {}
	Dictionary(const Dictionary &d) : c(d.c) {}
	Dictionary(const Container &_c) : c(_c) {}

	Dictionary &operator = (const Dictionary &d)
		{ c = d.c; return *this; }

	Iterator begin() { return c.begin(); }
	Iterator end() { return c.end(); }
	typename Const<Iterator>::type begin() const { return c.begin(); }
	typename Const<Iterator>::type end() const { return c.end(); }

	inline void insert(const key_t &k, const value_t &v = value_t())
		{ c.insert(pair_t(k, v)); }
	inline void remove(const key_t &k)
		{ c.remove(pair_t(k)); }
	inline bool exists(const key_t &k) const
		{ return c.exists(pair_t(k)); }
	
	inline value_t &find(const key_t &k)
		{ return c.find(pair_t(k))->value; }
	inline const value_t &find(const key_t &k) const
		{ return c.find(pair_t(k))->value; }
	
	inline size_t count() const
		{ return c.count(); }
	inline void clear()
		{ c.clear(); }
	inline void swap(Dictionary &d)
		{ c.swap(d.c); }
	inline void move(Dictionary &d)
		{ c.move(d.c); }
};


#endif


