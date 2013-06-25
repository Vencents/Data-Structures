#ifndef SET_H
#define SET_H

#include "BinarySearchTree.h"

template <typename T, typename Container = BinarySearchTree<T> >
class Set {
protected:
	mutable Container c;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;
	typedef typename Container::Iterator	Iterator;

	template <typename InputIter>
	void set(typename Const<InputIter>::type p, size_t n);
	void set(typename Const<ptr_t>::type p, size_t n);

	Set() : c() {}
	Set(const Set &s) : c(s.c) {}
	template <size_t N>
	Set(const value_t (&lst)[N]);
	Set(typename Const<ptr_t>::type p, size_t n);
		
	
	inline Set &operator = (const Set &s)
		{ c = s.c; return *this; }

	inline Iterator begin() const
		{ return c.begin(); }
	inline Iterator end() const
		{ return c.end(); }
	
	inline bool exists(const value_t &key) const
		{ return c.exists(key); }
	bool exists(const Set &s) const;
	
	inline void insert(const value_t &key)
		{ c.insert(key); }
	void insert(const Set &s);

	inline void remove(const value_t &key)
		{ c.remove(key); }
	void remove(const Set &s);

	inline const value_t *find(const value_t &k) const
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

