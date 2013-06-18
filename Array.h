#ifndef ARRAY_H
#define ARRAY_H

#include "Types.h"
#include "Iterator.h"
#include "Allocator.h"
#include "Exception.h"
#include "Algorithm.h"

template <typename Type, typename Alloc = Allocator >
class Array {
public:
	typedef Type				value_t;
	typedef Type				*ptr_t;
	typedef Type				&ref_t;
	typedef ptr_t				Iterator;
	typedef ::Reverser<Iterator>		Reverser;
protected:
	Object_Allocator<Type, Alloc> allocator;
	mutable ptr_t	buf_base;
	mutable ptr_t	buf_dend;
	mutable ptr_t	buf_end;

	void double_capacity();
public:

	Iterator begin()	{ return buf_base; }
	Iterator end()		{ return buf_dend; }
	Reverser rbegin()	{ return buf_dend; }
	Reverser rend()		{ return buf_base; }
	typename Const<Iterator>::type begin() const	{ return buf_base; }
	typename Const<Iterator>::type end() const	{ return buf_dend; }
	typename Const<Reverser>::type rbegin() const	{ return buf_dend; }
	typename Const<Reverser>::type rend() const	{ return buf_base; }
	Iterator from(ssize_t index);
	typename Const<Iterator>::type from(ssize_t index) const;

	Array &operator = (const Array &a);

	Array() : allocator(), buf_base(), buf_dend(), buf_end() {}
	Array(const Array &a) : allocator(), buf_base(), buf_dend(), buf_end() { this->operator = (a); }
	Array(size_t n);
	template <size_t N>
	Array(const value_t (&lst)[N]);
	template <typename InputIter>
	Array(typename Const<InputIter>::type p, size_t n);
	Array(typename Const<ptr_t>::type p, size_t n);
	~Array();

	template <typename InputIter>
	void set(typename Const<InputIter>::type p, size_t n);
	void set(typename Const<ptr_t>::type p, size_t n);
	void swap(const Array &a);
	inline void clear() { buf_dend = buf_base; }
	void resize(size_t n, typename Const<ref_t>::type val = value_t());
	void reserve(size_t n);
	inline size_t count() const
		{ return (buf_base != ptr_t()) ? buf_dend - buf_base : 0; }
	inline size_t capacity() const
		{ return (buf_base != ptr_t()) ? buf_end - buf_base : 0; }

//Fast	
	ref_t operator [] (ssize_t i);
	typename Const<ref_t>::type operator [] (ssize_t i) const;
	size_t push(typename Const<ref_t>::type val);
	value_t pop();
//Slow
	value_t shift();
	size_t unshift(typename Const<ref_t>::type val);
	size_t insert(ssize_t index, typename Const<ref_t>::type val);
	void remove(ssize_t index, size_t count);
	Array slice(ssize_t start, ssize_t length) const;
	Array splice(ssize_t start, size_t length, const Array &a) const;
	void fill(ssize_t start, size_t count, typename Const<ref_t>::type val);
//
	ssize_t find(typename Const<ref_t>::type val) const;
	ssize_t rfind(typename Const<ref_t>::type val) const;
	inline void reverse() { if (buf_base != ptr_t()) Algorithm::reverse(buf_base, buf_dend); }
	inline value_t first() const { return this->operator [] (0); }
	inline value_t last() const { return this->operator [] (-1); }	
};

#include "Array.tcc"

#endif
	
