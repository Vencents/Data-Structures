#ifndef MULTISET_H
#define MULTISET_H

#include "BinarySearchTree.h"

template <typename T, typename Container>
class Multiset_Iterator;

template <typename T>
class Multiset_Node {
public:
	T			key;
	mutable size_t	count;
	Multiset_Node() : key(), count() {}
	Multiset_Node(const T &k) : key(k), count(1) {}

	bool operator < (const Multiset_Node &m) const
		{ return key < m.key; }	
	bool operator == (const Multiset_Node &m) const
		{ return key == m.key; }
	bool operator != (const Multiset_Node &m) const
		{ return key != m.key; }
};

template <typename T, typename Container = BinarySearchTree<Multiset_Node<T> > >
class Multiset {
protected:
	typedef Multiset_Node<T>	node_t;
	mutable Container c;
	mutable size_t _count;
public:
	typedef T			value_t;
	typedef T			*ptr_t;
	typedef T			&ref_t;
	typedef Multiset_Iterator<T, Container>	Iterator;

	template <typename InputIter>
	void set(typename Const<InputIter>::type p, size_t n);
	void set(typename Const<ptr_t>::type p, size_t n);
	
	Multiset() : c(), _count() {}
	Multiset(const Multiset &m) : c(m.c), _count(m._count) {}
	template <size_t N>
	Multiset(const value_t (&lst)[N]);
	Multiset(typename Const<ptr_t>::type p, size_t n);
	
	Multiset &operator =(const Multiset &m);
	
	inline Iterator begin() const
		{ return Iterator(c.begin(), 0); }
	inline Iterator end() const
		{ return Iterator(c.end(), 0); }

	inline bool exists(const value_t &key)
		{ return c.exists(key); }
	bool exists(const Multiset &m);

	inline size_t count() const { return _count; }
	size_t countof(const value_t &key);
	
	void scale(size_t n);
	
	void insert(const value_t &key);
	void insert(const value_t &key, size_t n);
	void insert(const Multiset &m);
	
	void remove(const value_t &key);
	void remove(const value_t &key, size_t n);
	void remove(const Multiset &m);

	inline const value_t *find(const value_t &key) const
		{ return &c.find(key)->key; }
	inline void clear()
		{ c.clear(); }
	inline void move(Multiset &m)
		{ c.move(m.c); }
	inline void swap(Multiset &m)
		{ c.swap(m.c); }
};

template <typename T, typename Container>
class Multiset_Iterator {
	friend class Multiset<T, Container>;
protected:
	mutable size_t pos;
	mutable typename Container::Iterator it;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;

	Multiset_Iterator() : it(), pos() {}
	Multiset_Iterator(
		const Multiset_Iterator &i
	) : it(i.it), pos() {}
	Multiset_Iterator(
		typename Const<typename Container::Iterator>::type i,
		size_t p
	) : it(i), pos(p) {}

	const Multiset_Iterator &operator =(const Multiset_Iterator &i) const
		{ it = i.it; return *this; }
	
	const value_t &operator * () const
		{ return it->key; }
	const value_t *operator -> () const
		{ return &it->key; }
	
	const Multiset_Iterator &operator ++ () const {
		if (++pos == it->count) { ++it; pos = 0; }
		return *this;
	}
	const Multiset_Iterator &operator -- () const {
		if (pos == 0) { --it; pos = it->count - 1; }
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


#include "Multiset.tcc"

#endif