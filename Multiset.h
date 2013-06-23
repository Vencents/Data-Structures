#ifndef MULTISET_H
#define MULTISET_H

#include "Hashtable.h"

template <typename T>
class Multiset;

template <typename T>
class Multiset_Iterator {
	friend class Multiset<T>;
protected:
	mutable size_t pos;
	mutable typename Hashtable<T, size_t>::Iterator it;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;

	Multiset_Iterator() : it(), pos() {}
	Multiset_Iterator(
		const Multiset_Iterator &i
	) : it(i.it), pos() {}
	Multiset_Iterator(
		typename Const<typename Hashtable<T, size_t>::Iterator>::type i,
		size_t p
	) : it(i), pos(p) {}

	const Multiset_Iterator &operator =(const Multiset_Iterator &i) const
		{ it = i.it; return *this; }
	
	value_t operator * () const
		{ return it->key; }
	const ptr_t operator -> () const
		{ return &it->key; }
	
	const Multiset_Iterator &operator ++ () const {
		if (++pos == it->value) { ++it; pos = 0; }
		return *this;
	}
	const Multiset_Iterator &operator -- () const {
		if (pos == 0) { --it; pos = it->value - 1; }
		else --pos;
		return *this;
	}
	Multiset_Iterator operator ++ (int) const {
		Multiset_Iterator tmp(*this);
		this->operator ++(); 
		return tmp;
	}
	Multiset_Iterator operator -- (int) const {
		Multiset_Iterator tmp(*this);
		this->operator --();
		return tmp;
	}
	bool operator == (const Multiset_Iterator &i) const
		{ return it == i.it && pos == i.pos; }
	bool operator != (const Multiset_Iterator &i) const
		{ return pos != i.pos || it != i.it; }
};

template <typename T>
class Multiset {
protected:
	mutable Hashtable<T, size_t> c;
	size_t _count;
public:
	typedef T			value_t;
	typedef T			*ptr_t;
	typedef T			&ref_t;
	typedef Multiset_Iterator<T>	Iterator;

	template <typename InputIter>
	void set(typename Const<InputIter>::type p, size_t n);
	void set(typename Const<ptr_t>::type p, size_t n);
	
	Multiset() : c(), _count() {}
	Multiset(const Multiset &m) : c(m.c), _count(m._count) {}
	template <size_t N>
	Multiset(const value_t (&lst)[N]);
	Multiset(typename Const<ptr_t>::type p, size_t n);
	
	Multiset &operator =(const Multiset &m);
	
	Iterator begin();
	Iterator end();
	typename Const<Iterator>::type begin() const;
	typename Const<Iterator>::type end() const;

	bool contains(typename Const<ref_t>::type val);
	bool contains(const Multiset &m);

	inline size_t count() const { return _count; }
	size_t countof(typename Const<ref_t>::type val);
	
	void scale(size_t n);
	
	void insert(typename Const<ref_t>::type val);
	void insert(typename Const<ref_t>::type val, size_t n);
	void insert(const Multiset &m);
	
	void remove(typename Const<ref_t>::type val);
	void remove(typename Const<ref_t>::type val, size_t n);
	void remove(const Multiset &m);

	void retain(const Multiset &m);
	
	inline void clear()
		{ c.clear(); }
	inline void move(Multiset &m)
		{ c.move(m.c); }
	inline void swap(Multiset &m)
		{ c.swap(m.c); }
};

#include "Multiset.tcc"

#endif
