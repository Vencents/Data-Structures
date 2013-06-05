#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Types.h"
#include "Iterator.h"
#include "Allocator.h"
#include "Exception.h"

template <typename T>
class Linkedlist_Node {
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;

	value_t val;
	Linkedlist_Node *prev, *next;

	Linkedlist_Node() : prev(), next() {}
	Linkedlist_Node(const Linkedlist_Node &n) : val(n.val), prev(n.prev), next(n.next) {}
	Linkedlist_Node &operator =(const Linkedlist_Node &n)
		{ val = value_t(n.val); prev = n.prev; next = n.next; return *this; }
	inline void construct(typename Const<ref_t>::type v)
		{ new ((void*)&val)value_t(v); }
	inline void destroy()
		{ ((value_t*)&val)->~value_t(); }

};

template <typename Type, typename Alloc>
class Linkedlist;

template <typename Type, typename Alloc>
class Linkedlist_Iterator {
	friend class Linkedlist<Type, Alloc>;
protected:
	mutable Linkedlist_Node<Type> *curr;
public:
	typedef Type value_t;
	typedef Type *ptr_t;
	typedef Type &ref_t;

	Linkedlist_Iterator() : curr() {}
	Linkedlist_Iterator(const Linkedlist_Iterator &i) : curr(i.curr) {}
	Linkedlist_Iterator(Linkedlist_Node<Type> * const node) : curr(node) {}

	ref_t operator * () { return curr->val; }
	const ref_t operator * () const { return curr->val; }
	ptr_t operator -> () { return &curr->val; }
	const ptr_t operator -> () const { return &curr->val; }
	const Linkedlist_Iterator &operator ++ () const;
	const Linkedlist_Iterator &operator -- () const;
	Linkedlist_Iterator operator ++ (int) const;
	Linkedlist_Iterator operator -- (int) const;
	bool operator == (const Linkedlist_Iterator &i) const;
	bool operator != (const Linkedlist_Iterator &i) const;
	
};

template <typename Type, typename Alloc = Allocator< Linkedlist_Node<Type> > >
class Linkedlist {
public:
	typedef Type	value_t;
	typedef Type	*ptr_t;
	typedef Type	&ref_t;
	typedef Linkedlist_Iterator<Type, Alloc>	Iterator;
	typedef ::Reverser<Iterator>			Reverser;
protected:
	size_t _count;
	Alloc	allocator;
	/* base_node links right before the first element, end_node links right after the last element */
	Linkedlist_Node<Type> base_node, end_node;
public:
	Linkedlist();
	Linkedlist(const Linkedlist &l);
	Linkedlist(size_t n);
	template <typename InputIter>
	Linkedlist(typename Const<InputIter>::type p, size_t n);
	Linkedlist(typename Const<ptr_t>::type p, size_t n);
	~Linkedlist();

	Iterator begin();
	Iterator end();
	typename Const<Iterator>::type begin() const;
	typename Const<Iterator>::type end() const;
	Reverser rbegin();
	Reverser rend();
	typename Const<Reverser>::type rbegin() const;
	typename Const<Reverser>::type rend() const;

	template <typename InputIter>
	void set(typename Const<InputIter>::type p, size_t n);
	void set(typename Const<ptr_t>::type p, size_t n);
	void swap(const Linkedlist &l);
	void clear();
	void resize(size_t n, typename Const<ref_t>::type val = value_t());
	size_t count() const { return _count; }
	value_t first();
	value_t last();
//Fast
	size_t push(typename Const<ref_t>::type val);
	value_t pop();
	size_t unshift(typename Const<ref_t>::type val);
	value_t shift();
	size_t insert(Iterator pos, typename Const<ref_t>::type val);
	void remove(Iterator pos, size_t count = 1);
	void fill(Iterator pos, size_t n, typename Const<ref_t>::type val);
//Slow
	ref_t operator [] (ssize_t index);
	typename Const<ref_t>::type operator [] (ssize_t index) const;
	Iterator find(typename Const<ref_t>::type val) const;
	Iterator rfind(typename Const<ref_t>::type val) const;
	Iterator from(ssize_t index);
	typename Const<Iterator>::type from(ssize_t index) const;

	inline size_t insert(ssize_t pos, typename Const<ref_t>::type val)
		{ return this->insert(this->from(pos), val); }
	inline void remove(ssize_t pos, size_t count = 1)
		{ this->remove(this->from(pos), count); }
	inline void fill(ssize_t pos, size_t n, typename Const<ref_t>::type val)
		{ this->fill(this->from(pos), n, val); }

};	

#include "Linkedlist.tcc"

#endif
