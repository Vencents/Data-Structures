#ifndef DEQUE_H
#define DEQUE_H

#include "Linkedlist.h"

template <typename T, typename Container = Linkedlist<T> >
class Deque {
protected:
	Container c;
public:
	typedef typename Container::value_t	value_t;
	typedef typename Container::ref_t	ref_t;

	Deque() : c() {}
	Deque(const Deque &d) : c(d.c) {}
	Deque(const Container &_c) : c(_c) {}

	inline void push(typename Const<ref_t>::type val)
		{ c.push(val); }
	
	inline value_t pop()
		{ return c.pop(); }

	inline void unshift(typename Const<ref_t>::type val)
		{ c.unshift(val); }

	inline value_t shift()
		{ return c.shift(); }

	inline value_t first() const
		{ return c.first(); }

	inline value_t last() const
		{ return c.last(); }

	inline size_t count() const
		{ return c.count(); }

	inline void clear()
		{ c.clear(); }

	inline void move(Deque &d)
		{ c.move(d.c); }

	inline void swap(Deque &d)
		{ c.swap(d.c); }
};

#endif
