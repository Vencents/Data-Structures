#ifndef SET_H
#define SET_H

#include "Hashtable.h"
#include <stdarg.h>

template <typename T>
class Set;

template <typename T>
class Set_Iterator {
	friend class Set<T>;
protected:
	typename Hashtable<T, T>::Iterator it;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;

	Set_Iterator() : it() {}
	Set_Iterator(const Set_Iterator &i) : it(i.it) {}
	Set_Iterator(typename Const<typename Hashtable<T, T>::Iterator>::type i) : it(i) {}

	Set_Iterator &operator =(const Set_Iterator &i) { it = i.it; return *this; }
	
	value_t operator * () const { return it->key; }
	const ptr_t operator -> () const { return &it->key; }
	
	const Set_Iterator &operator ++ () const { ++it; return *this; }
	const Set_Iterator &operator -- () const { --it; return *this; }
	Set_Iterator operator ++ (int) const {
		Set_Iterator tmp(*this);
		++it;
		return tmp;
	}
	Set_Iterator operator -- (int) const {
		Set_Iterator tmp(*this);
		--it;
		return tmp;
	}
	bool operator == (const Set_Iterator &i) const
		{ return it == i.it; }
	bool operator != (const Set_Iterator &i) const
		{ return it != i.it; }		
};

template <typename T>
class Set {
protected:
	mutable Hashtable<T, T> c;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;
	typedef Set_Iterator<T>	Iterator;

	template <typename InputIter>
	void set(typename Const<InputIter>::type p, size_t n) {
		c.clear();
		for (size_t i = 0; i < n; ++i, ++p) c[*p];
	}
	void set(typename Const<ptr_t>::type p, size_t n)
		{ this->set<ptr_t>(p, n); }

	Set() : c() {}
	Set(const Set &s) : c(s.c) {}
	template <size_t N>
	Set(const value_t (&lst)[N]) : c()
		{ this->set<ptr_t>((ptr_t)lst, N); }
	Set(typename Const<ptr_t>::type p, size_t n) : c()
		{ this->set<ptr_t>(p, n); }
		
	
	Set &operator = (const Set &s)
		{ c = s.c; return *this; }

	Iterator begin() { return Iterator(c.begin()); }
	Iterator end() { return Iterator(c.end()); }
	typename Const<Iterator>::type begin() const { return Iterator(c.begin()); }
	typename Const<Iterator>::type end() const { return Iterator(c.end()); }
		
	bool contains(typename Const<ref_t>::type val) const
		{ return c.contains(val); }
	bool contains(const Set &s) const {
		Iterator it, end = s.end();
		for (it = s.begin(); it != end; ++it)
			if (!c.contains(it.it->key)) { return false; }
		return true;
	}
	
	void insert(typename Const<ref_t>::type val)
		{ c[val]; }
	void insert(const Set &s) {
		Iterator it, end = s.end();
		for (it = s.begin(); it != end; ++it)
			c[it.it->key];
	}

	void remove(typename Const<ref_t>::type val)
		{ c.remove(val); }
	void remove(const Set &s) {
		Iterator it, end = s.end();
		for (it = s.begin(); it != end; ++it) {
			try { c.remove(it.it->key); } catch(Exception &e) {}
		}
	}

	void retain(const Set &s) {
		Iterator it(c.begin()), end(c.end());
		while (it != end) {
			if (!s.contains(it.it->key))
				it.it = c.remove(it.it);
			else ++it;
		}
	}

	size_t count() const
		{ return c.count(); }
	
	void clear()
		{ c.clear(); }

	void move(Set &s)
		{ c.move(s.c); }

	void swap(Set &s)
		{ c.swap(s.c); }

};
	

#endif

