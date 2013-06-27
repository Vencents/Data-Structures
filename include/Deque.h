#ifndef DEQUE_H
#define DEQUE_H

#include "Linkedlist.h"

template <typename T, typename Container = Linkedlist<T> >
class Deque {
protected:
	Container c;
public:
	typedef typename Container::value_t	value_t;

	Deque() : c() {}
	Deque(const Deque &d) : c(d.c) {}
	Deque(const Container &_c) : c(_c) {}

	Deque &operator = (const Deque &d)
		{ c = d.c; return *this; }

	inline void push(const T &val)
		{ c.push(val); }
	
	inline T pop()
		{ return c.pop(); }

	inline void unshift(const T &val)
		{ c.unshift(val); }

	inline T shift()
		{ return c.shift(); }

	inline T first() const
		{ return c.first(); }

	inline T last() const
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
