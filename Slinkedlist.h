#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H
#include "Algorithm.h"
#include "Allocator.h"
#include "Exception.h"

template <typename T>
class Slinkedlist_Node {
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;

	value_t val;
	Slinkedlist_Node *next;

	Slinkedlist_Node() : next() {}
	Slinkedlist_Node(const Slinkedlist_Node &n) : val(n.val), next(n.next) {}
	
	Slinkedlist_Node &operator =(const Slinkedlist_Node &n)
		{ val = value_t(n.val); next = n.next; return *this; }
	inline void construct(typename Const<ref_t>::type v)
		{ new ((void*)&val)value_t(v); }
	inline void destroy()
		{ ((value_t*)&val)->~value_t(); }
};

template <typename T, typename Alloc>
class Slinkedlist;

template <typename T, typename Alloc>
class Slinkedlist_Iterator {
	friend class Slinkedlist<T, Alloc>;
protected:
	mutable Slinkedlist_Node<T> *curr;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;

	Slinkedlist_Iterator() : curr() {}
	Slinkedlist_Iterator(const Slinkedlist_Iterator &i) : curr(i.curr) {}
	Slinkedlist_Iterator(Slinkedlist_Node<T> * const node) : curr(node) {}
		
	ref_t operator * () { return curr->val; }
	const ref_t operator * () const { return curr->val; }
	ptr_t operator -> () { return &curr->val; }
	const ptr_t operator -> () const { return &curr->val; }
	const Slinkedlist_Iterator &operator ++ () const;
	const Slinkedlist_Iterator operator ++ (int) const;
	inline bool operator == (const Slinkedlist_Iterator &i) const
		{ return curr = i.curr; }
	inline bool operator != (const Slinkedlist_Iterator &i) const
		{ return curr != i.curr; }
};

template <typename T, typename Alloc = Allocator>
class Slinkedlist {
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;
	typedef Slinkedlist_Iterator<T, Alloc>	Iterator;
protected:
	size_t _count;
	Object_Allocator<Slinkedlist_Node<T>, Alloc> allocator;
	Slinkedlist_Node<T> *front, *back, before_front;
public:	
	Slinkedlist() :
		front(), back(), _count(), allocator() {}
	Slinkedlist(const Slinkedlist &l) :
		front(l.front), back(l.back),
		_count(l.count), allocator() {}
	Slinkedlist(size_t n, typename Const<ref_t>::type val = value_t());
	template <size_t N>
	Slinkedlist(const value_t (&lst)[N]);
	template <typename InputIter>
	Slinkedlist(typename Const<InputIter>::type p, size_t n);
	Slinkedlist(typename Const<ptr_t>::type p, size_t n);
	~Slinkedlist();

	void move(Slinkedlist &t);	
	void swap(Slinkedlist &t);

	Iterator begin();
	Iterator end();
	Iterator beforeBegin();
	Iterator beforeEnd();
	typename Const<Iterator>::type begin() const;
	typename Const<Iterator>::type end() const;
	typename Const<Iterator>::type beforeBegin() const;
	typename Const<Iterator>::type beforeEnd() const;
	
	template <typename InputIter>
	void set(typename Const<InputIter>::type p, size_t n);
	void set(typename Const<ptr_t>::type p, size_t n);	
	void swap(const Slinkedlist &l);
	void clear();
	void resize(size_t n, typename Const<ref_t>::type val = value_t());
	size_t count() const { return _count; }
	value_t first() const;
	value_t last() const;

	size_t unshift(typename Const<ref_t>::type val);
	value_t shift();

	void insertAfter(Iterator before, typename Const<ref_t>::type val);
	void removeAfter(Iterator before, size_t n = 1);
	
	Iterator findBefore(typename Const<ref_t>::type val) const;
	Iterator rfindBefore(typename Const<ref_t>::type val) const;	
	Iterator find(typename Const<ref_t>::type val) const;
	Iterator rfind(typename Const<ref_t>::type val) const;

	ref_t operator [] (ssize_t index);
	typename Const<ref_t>::type operator [] (ssize_t index) const;
	Iterator from(ssize_t index);
	typename Const<Iterator>::type from(ssize_t index) const;	


};

#include "Slinkedlist.tcc"

#endif
