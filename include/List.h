#ifndef LIST_H
#define LIST_H

#include "Array.h"

template <typename T, typename Container = Array<T> >
class List {
protected:
	Container c;
public:
	typedef T	value_t;
	typedef typename Container::Iterator		Iterator;
	typedef typename Container::Const_Iterator	Const_Iterator;

	List() : c() {}
	List(const List &t) : c(t.c) {}
	List(const Container &_c) : c(_c) {}

	List &operator = (const List &t)
		{ c = t.c; return *this; }

	inline Iterator begin()
		{ return c.begin(); }
	inline Iterator end()
		{ return c.end(); }
	inline Const_Iterator  begin() const
		{ return c.begin(); }
	inline Const_Iterator end() const
		{ return c.end(); }

	inline size_t push(const T &val)
		{ return c.push(val); }
	inline T pop()
		{ return c.pop(); }
	inline size_t unshift(const T &val)
		{ return c.unshift(val); }
	inline T shift()
		{ return c.shift(); }

	inline size_t count() const
		{ return c.count(); }
	inline void clear()
		{ c.clear(); }

	inline size_t insert(ssize_t pos, const T &val)
		{ return c.insert(pos, val); }
	inline void remove(ssize_t pos, size_t count = 1)
		{ c.remove(pos, count); }

	inline Iterator insertAt(Iterator it, const T &val)
		{ return c.insertAt(it, val); }
	inline Iterator removeAt(Iterator it, size_t n = 1)
		{ return c.removeAt(it, n); }
	
	inline T &operator [] (ssize_t index)
		{ return c.operator [](index); }
	inline const T &operator [] (ssize_t index) const
		{ return c.operator [](index); }

	inline void swap(List &t)
		{ c.swap(t.c); }
	inline void move(List &t)
		{ c.move(t.c); }
};

#endif
