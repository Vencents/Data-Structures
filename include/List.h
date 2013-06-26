#ifndef LIST_H
#define LIST_H

#include "Array.h"

template <typename T, typename Container = Array<T> >
class List {
protected:
	Container c;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;
	typedef typename Container::Iterator Iterator;

	List() : c() {}
	List(const List &t) : c(t.c) {}
	List(const Container &_c) : c(_c) {}

	List &operator = (const List &t)
		{ c = t.c; return *this; }

	inline Iterator begin()
		{ return c.begin(); }
	inline Iterator end()
		{ return c.end(); }
	inline typename Const<Iterator>::type begin() const
		{ return c.begin(); }
	inline typename Const<Iterator>::type end() const
		{ return c.end(); }

	inline size_t push(const value_t &val)
		{ return c.push(val); }
	inline value_t pop()
		{ return c.pop(); }
	inline size_t unshift(const value_t &val)
		{ return c.unshift(val); }
	inline value_t shift()
		{ return c.shift(); }

	inline size_t count() const
		{ return c.count(); }
	inline void clear()
		{ c.clear(); }

	inline size_t insert(ssize_t pos, const value_t &val)
		{ return c.insert(pos, val); }
	inline void remove(ssize_t pos, size_t count = 1)
		{ c.remove(pos, count); }
	
	inline value_t &operator [] (ssize_t index)
		{ return c.operator [](index); }
	inline const value_t &operator [] (ssize_t index) const
		{ return c.operator [](index); }

	inline void swap(List &t)
		{ c.swap(t.c); }
	inline void move(List &t)
		{ c.move(t.c); }
};

#endif
