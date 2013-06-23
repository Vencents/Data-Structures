#ifndef QUEUE_H
#define QUEUE_H

#include "Linkedlist.h"
#include "Types.h"

template <typename T, typename Container = Linkedlist<T> >
class Queue {
protected:
	Container c;
public:
	typedef typename Container::value_t	value_t;
	typedef typename Container::ref_t	ref_t;
	
	Queue() : c() {}
	Queue(const Queue &q) : c(q.c) {}
	Queue(const Container &_c) : c(_c) {}
	
	inline void push(typename Const<ref_t>::type val)
		{ c.push(val); }

	inline value_t pop()
		{ return c.shift(); }

	inline value_t peek()
		{ return c.first(); }

	inline size_t count()
		{ return c.count(); }

	inline void clear()
		{ c.clear(); }
	
	inline void move(Queue &q)
		{ c.move(q.c); }

	inline void swap(Queue &q)
		{ c.swap(q.c); }
};
#endif
