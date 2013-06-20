#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "Array.h"

template <typename T, typename Container = Array<T> >
class Ringbuffer {
public:
	typedef typename Container::value_t	value_t;
	typedef typename Container::ptr_t	ptr_t;
	typedef typename Container::ref_t	ref_t;
protected:
	Container c;
	typename Container::Iterator front, rear;
	size_t front_index, rear_index, _count;
	inline void next(typename Container::Iterator &it, size_t &i) {
		++it;
		++i;
		if (it == c.end()) {
			it = c.begin();
			i = 0;
		}
	}
	inline void prev(typename Container::Iterator &it, size_t &i) {
		--it;
		--i;
		if (it == c.begin()) {
			it = c.end();
			--it;
			i = c.count() - 1;
		}
	}
public:
	void move(Ringbuffer &r);
	void swap(Ringbuffer &r);

	Ringbuffer(size_t size);
	Ringbuffer(const Ringbuffer &r);
	Ringbuffer(const Container &container);

	size_t push(typename Const<ref_t>::type val);
	value_t pop();
	size_t unshift(typename Const<ref_t>::type val);
	value_t shift();
	
	void resize(size_t n);
	ref_t operator [] (ssize_t index);
	typename Const<ref_t>::type operator [] (ssize_t index) const;
	
	inline value_t first() const { return this->operator [] (0); }
	inline value_t last() const { return this->operator [] (-1); }	

	inline size_t count() const { return _count; }
	inline void clear() {
		_count = 0;
		front = rear = c.begin();
		front_index = rear_index = 0;
	}
	
};

#include "Ringbuffer.tcc"

#endif
