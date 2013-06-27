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
	
	Queue() : c() {}
	Queue(const Queue &q) : c(q.c) {}
	Queue(const Container &_c) : c(_c) {}

	Queue &operator = (const Queue &q)
		{ c = q.c; return *this; }
	
	inline void push(const T &val)
		{ c.push(val); }

	inline T pop()
		{ return c.shift(); }

	inline T peek()
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
