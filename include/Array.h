#ifndef ARRAY_H
#define ARRAY_H

#include "Types.h"
#include "Iterator.h"
#include "Allocator.h"
#include "Exception.h"
#include "Algorithm.h"

template <typename T, typename Alloc = Allocator>
class Array {
public:
	typedef T				value_t;
	
	typedef T				*Iterator;
	typedef ::Reverser<Iterator>	Reverser;

	typedef typename Const<Iterator>::type	Const_Iterator;
	typedef typename Const<Reverser>::type	Const_Reverser;
protected:
	T *_base;
	T *_dend;
	T *_end;
	Object_Allocator<T, Alloc>	allocator;

	void double_capacity();

public:
	template <typename InputIter>
	void set(InputIter it, size_t n);
	void resize(size_t n);
	void resize(size_t n, const T &val);

	Array() : _base(), _dend(), _end(), allocator() {}
	Array(const Array &a) : 
		_base(), _dend(), _end(), allocator() 
		{ this->operator = (a); }
	Array(size_t n) :
		_base(), _dend(), _end(), allocator()
		{ this->resize(n); }
	Array(size_t n, const T &val) :
		_base(), _dend(), _end(), allocator()
		{ this->resize(n, val); }
	Array(const T *p, size_t n) :
		_base(), _dend(), _end(), allocator()
		{ this->set<const T*>(p, n); }
	~Array();

	Array &operator = (const Array &a) {
		this->set<const T*>(a._base, a._dend - a._base);
		return *this;
	}

	inline Iterator begin()
		{ return _base; }
	inline Iterator end()
		{ return _dend; }
	inline Const_Iterator begin() const
		{ return _base; }
	inline Const_Iterator end() const
		{ return _dend; }

	inline Reverser rbegin()
		{ return _dend; }
	inline Reverser rend()
		{ return _base; }
	inline Const_Reverser rbegin() const
		{ return _dend; } 
	inline Const_Reverser rend() const
		{ return _base; }

	void move(Array &a);
	void swap(Array &a);

	void set(const T *p, size_t n)
		{ this->set<const T*>(p, n); }
	
	inline void clear()
		{ _dend = _base; }
	inline size_t count() const
		{ return _base ? _dend - _base : 0; }

	T &operator [] (ssize_t i);
	const T &operator [](ssize_t i) const;

	inline const T &first() const
		{ return operator [] (0); }
	inline const T &last() const
		{ return operator [] (-1); }
	
	void push(const T &val);
	T pop();

	void unshift(const T &val);
	T shift();

	void insert(ssize_t index, const T &val);
	Iterator insertAt(Iterator pos, const T &val);

	void remove(ssize_t index, size_t n);
	Iterator removeAt(Iterator pos, size_t n);

	Array slice(ssize_t first, size_t n) const;
	Array sliceAt(Iterator pos, size_t n) const;
};	

#include "Array.tcc"

#endif
