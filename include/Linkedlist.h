#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Types.h"
#include "Iterator.h"
#include "Allocator.h"
#include "Exception.h"
#include "Algorithm.h"

template <typename T>
class Linkedlist_Node {
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;

	value_t val;
	Linkedlist_Node *prev, *next;

	Linkedlist_Node() : prev(), next() {}
	Linkedlist_Node(const Linkedlist_Node &n) :
		val(n.val), prev(n.prev), next(n.next) {}
	Linkedlist_Node &operator =(const Linkedlist_Node &n)
		{ val = value_t(n.val); prev = n.prev; next = n.next; return *this; }
	inline void construct()
		{ new ((void*)&val)value_t(); }
	inline void construct(typename Const<ref_t>::type v)
		{ new ((void*)&val)value_t(v); }
	inline void destroy()
		{ ((value_t*)&val)->~value_t(); }

};

template <typename Type, typename Alloc>
class Linkedlist_Iterator;

template <typename Type, typename Alloc = Allocator>
class Linkedlist {
public:
	typedef Type	value_t;
	typedef Type	*ptr_t;
	typedef Type	&ref_t;
	typedef Linkedlist_Iterator<Type, Alloc>	Iterator;
	typedef ::Reverser<Iterator>			Reverser;
protected:
	typedef typename Const<ref_t>::type const_ref_t;
	size_t _count;
	Object_Allocator<Linkedlist_Node<Type>, Alloc> allocator;
	mutable Linkedlist_Node<Type> base_node, end_node;
public:
	Linkedlist();
	Linkedlist(const Linkedlist &l);
	Linkedlist(size_t n);
	template <size_t N>
	Linkedlist(const value_t (&lst)[N]);
	template <typename InputIter>
	Linkedlist(typename Const<InputIter>::type p, size_t n);
	Linkedlist(typename Const<ptr_t>::type p, size_t n);
	~Linkedlist();

	void move(Linkedlist &t);
	void swap(Linkedlist &t);

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
	void set(const value_t *p, size_t n);
	Linkedlist &operator =(const Linkedlist &t)
		{ this->set<Iterator>(t.begin(), t.count()); return *this; }
	void clear();
	void resize(size_t n, const value_t &val = value_t());
	size_t count() const { return _count; }
	inline const value_t &first() const {
		if (base_node.next == &end_node) throw Enodata();
		return base_node.next->val;
	}
	inline const value_t &last() const {
		if (end_node.prev == &base_node) throw Enodata();
		return end_node.prev->val;
	}	

	size_t push(const value_t &val);
	value_t pop();
	size_t unshift(const value_t &val);
	value_t shift();
	size_t insert(Iterator pos, const value_t &val);
	void remove(Iterator pos, size_t count = 1);
	void fill(Iterator pos, size_t n, const value_t &val);

	ref_t operator [] (ssize_t index);
	typename Const<ref_t>::type operator [] (ssize_t index) const;
	Iterator find(const value_t &val) const;
	Iterator rfind(const value_t &val) const;
	Iterator from(ssize_t index);
	typename Const<Iterator>::type from(ssize_t index) const;

	inline size_t insert(ssize_t pos, const value_t &val)
		{ return this->insert(this->from(pos), val); }
	inline void remove(ssize_t pos, size_t count = 1)
		{ this->remove(this->from(pos), count); }
	inline void fill(ssize_t pos, size_t n, const value_t &val)
		{ this->fill(this->from(pos), n, val); }

};	

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

	const Linkedlist_Iterator &operator = (const Linkedlist_Iterator &t) const
		{ curr = t.curr; return *this; }

	value_t &operator * () { return curr->val; }
	const value_t &operator * () const { return curr->val; }
	value_t *operator -> () { return &curr->val; }
	const value_t *operator -> () const { return &curr->val; }
	const Linkedlist_Iterator &operator ++ () const;
	const Linkedlist_Iterator &operator -- () const;
	Linkedlist_Iterator operator ++ (int) const;
	Linkedlist_Iterator operator -- (int) const;
	bool operator == (const Linkedlist_Iterator &i) const;
	bool operator != (const Linkedlist_Iterator &i) const;
	
};


#include "Linkedlist.tcc"

#endif
