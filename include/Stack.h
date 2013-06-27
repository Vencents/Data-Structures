#ifndef STACK_H
#define STACK_H

#include "Array.h"
#include "Types.h"

template <typename T, typename Container = Array<T> >
class Stack {
protected:
	Container c;
public:
	typedef typename Container::value_t	value_t;

	Stack() : c() {}
	Stack(const Stack &s) : c(s.c) {}
	Stack(const Container &container) : c(container) {}

	Stack &operator = (const Stack &s)
		{ c = s.c; return *this; }
	
	inline void push(const T &val)
		{ c.push(val); }

	inline T pop()
		{ return c.pop(); }

	inline T peek()
		{ return c.last(); }

	inline size_t count()
		{ return c.count(); }

	inline void clear()
		{ c.clear(); }

	inline void move(Stack &s)
		{ c.move(s.c); }

	inline void swap(Stack &s)
		{ c.swap(s.c); }	
};


#endif

