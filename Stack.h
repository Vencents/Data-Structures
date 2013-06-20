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
	typedef typename Container::ref_t	ref_t;

	Stack() : c() {}
	Stack(const Stack &s) : c(s.c) {}
	Stack(const Container &container) : c(container) {}
	
	inline void push(typename Const<ref_t>::type val)
		{ c.push(val); }

	inline value_t	pop()
		{ return c.pop(); }

	inline value_t peek()
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

