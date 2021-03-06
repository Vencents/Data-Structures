#ifndef SET_H
#define SET_H

#include "BinarySearchTree.h"

template <typename T, typename Container = BinarySearchTree<T> >
class Set {
protected:
	mutable Container c;
public:
	typedef T	value_t;
	typedef typename Container::Iterator	Iterator;

	Set() : c() {}
	Set(const Set &s) : c(s.c) {}
	Set(const Container &_c) : c(_c) {}
	
	inline Set &operator = (const Set &s)
		{ c = s.c; return *this; }

	inline Iterator begin() const
		{ return c.begin(); }
	inline Iterator end() const
		{ return c.end(); }
	
	inline bool exists(const T &key) const
		{ return c.exists(key); }
	bool exists(const Set &s) const;
	
	inline void insert(const T &key)
		{ c.insert(key); }
	void insert(const Set &s);

	inline void remove(const T &key)
		{ c.remove(key); }
	void remove(const Set &s);

	inline const T *find(const T &k) const
		{ return c.find(k); }
	inline size_t count() const
		{ return c.count(); }
	inline void clear()
		{ c.clear(); }
	inline void move(Set &s)
		{ c.move(s.c); }
	inline void swap(Set &s)
		{ c.swap(s.c); }

};

#include "Set.tcc"	

#endif

