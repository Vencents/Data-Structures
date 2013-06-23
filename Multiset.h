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
	Multiset_Iterator(const Multiset_Iterator &i) : it(i.it), pos() {}
	Multiset_Iterator(typename Const<typename Hashtable<T, size_t>::Iterator>::type i, size_t p) : it(i), pos(p) {}
	
	const Multiset_Iterator &operator =(const Multiset_Iterator &i) const
		{ it = i.it; return *this; }

	value_t operator * () const { return it->key; }
	const ptr_t operator -> () const { return &it->key; }

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
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;
	typedef Multiset_Iterator<T>	Iterator;

	template <typename InputIter>
	void set(typename Const<InputIter>::type p, size_t n) {
		_count = 0;
		c.clear();
		for (size_t i = 0; i < n; ++i, ++p) {
			++c[*p];
			++_count;
		}
	}
	void set(typename Const<ptr_t>::type p, size_t n)
		{ this->set<ptr_t>(p, n); }

	Multiset() : c(), _count() {}
	Multiset(const Multiset &m) : c(m.c), _count(m._count) {}
	template <size_t N>
	Multiset(const value_t (&lst)[N]) : c(), _count()
		{ this->set<ptr_t>((ptr_t)lst, N); }
	Multiset(typename Const<ptr_t>::type p, size_t n) : c(), _count()
		{ this->set<ptr_t>(p, n); }

	Multiset &operator =(const Multiset &m)
		{ c = m.c; _count = m._count; return *this; }

	Iterator begin() { return Iterator(c.begin(), 0); }
	Iterator end() { return Iterator(c.end(), 0); }
	typename Const<Iterator>::type begin() const
		{ return Iterator(c.begin(), 0); }
	typename Const<Iterator>::type end() const
		{ return Iterator(c.end(), 0); }

	bool contains(typename Const<ref_t>::type val)
		{ return c.contains(val); }
	bool contains(const Multiset &m) {
		typename Hashtable<T, size_t>::Iterator it(m.c.begin()), end(m.c.end());
		for (; it != end; ++it) {
			if (c.contains(it->key)) {
				if (it->value != c[it->key]) return false;
			} else return false;
		}
		return true;
	}

	inline size_t count() const { return _count; }
	size_t countof(typename Const<ref_t>::type val)
		{ return c[val]; }
	
	void scale(size_t n) {
		typename Hashtable<T, size_t>::Iterator it(c.begin()), end(c.end());
		for (; it != end; ++it) {
			_count -= it->value;
			it->value *= n;
			_count += it->value;
		}
	}	

	void insert(typename Const<ref_t>::type val)
		{ ++c[val]; ++_count; }
	void insert(typename Const<ref_t>::type val, size_t n)
		{ c[val] += n; _count += n; }
	void insert(const Multiset &m) {
		typename Hashtable<T, size_t>::Iterator it(m.c.begin()), end(m.c.end());
		for (; it != end; ++it) {
			c[it->key] += it->value;
		}
	}
	
	void remove(typename Const<ref_t>::type val) {
		if (c.contains(val) == false) throw Erange();
		size_t &v = c[val];
		if (--v == 0) c.remove(val);
	}
	void remove(typename Const<ref_t>::type val, size_t n) {
		if (c.contains(val) == false) throw Erange();
		size_t *i = &c[val];
		if (*i < n) *i = 0;
		else *i -= n;	
	}
	void remove(const Multiset &m) {
		size_t *n;
		typename Hashtable<T, size_t>::Iterator it(m.c.begin()), end(m.c.end());
		for (; it != end; ++it) {
			if (c.contains(it->key)) {
				n = &c[it->key];
				if (it->value >= *n) {
					_count -= *n;
					c.remove(it->key);
				} else {
					_count -= it->value;
					*n -= it->value;
				}	
			}
		}
	}

	void retain(const Multiset &m) {
		size_t *i;
		typename Hashtable<T, size_t>::Iterator it(m.c.begin()), end(m.c.end());
		for (; it != end; ++it) {
			if (!c.contains(it->key)) c.remove(it->key);
			else {
				i = &c[it->key];
				if (*i > it->value) *i = it->value;
			}
		}
	}

	void clear()
		{ c.clear(); }
	void move(Multiset &m)
		{ c.move(m.c); }
	void swap(Multiset &m)
		{ c.swap(m.c); }
};
	
#endif
