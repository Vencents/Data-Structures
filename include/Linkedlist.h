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

	T	value;
	Linkedlist_Node *prev, *next;

	Linkedlist_Node() : prev(), next() {}
	Linkedlist_Node(const Linkedlist_Node &n) :
		value(n.value), prev(n.prev), next(n.next) {}
	Linkedlist_Node &operator =(const Linkedlist_Node &n)
		{ value = value_t(n.val); prev = n.prev; next = n.next; return *this; }

	inline void construct()
		{ new ((void*)&value)value_t(); }
	inline void construct(const T &v)
		{ new ((void*)&value)value_t(v); }
	inline void destroy()
		{ ((value_t*)&value)->~value_t(); }

};

template <typename T, typename Alloc>
class Linkedlist_Iterator;

template <typename T, typename Alloc = Allocator>
class Linkedlist {
public:
	typedef T	value_t;

	typedef Linkedlist_Iterator<T, Alloc>	Iterator;
	typedef ::Reverser<Iterator>			Reverser;
	
	typedef typename Const<Iterator>::type	Const_Iterator;
	typedef typename Const<Reverser>::type	Const_Reverser;
protected:
	typedef Linkedlist_Node<T>	node_t;

	size_t		_count;
	mutable node_t	head, tail;
	Object_Allocator<node_t, Alloc>	allocator;
public:
	template <typename InputIter>
	void set(InputIter it, size_t n);
	void resize(size_t n);
	void resize(size_t n, const T &val);

	Linkedlist();
	Linkedlist(const Linkedlist &t);
	Linkedlist(size_t n);
	Linkedlist(size_t n, const T &val);
	Linkedlist(const T *p, size_t n);
	~Linkedlist()
		{ this->clear(); }

	Linkedlist &operator =(const Linkedlist &t)
		{ this->set<Iterator>(t.begin(), t.count()); return *this; }

	inline Iterator begin()
		{ return Iterator(head.next, 0); }
	inline Iterator end()
		{ return Iterator(&tail, _count); }
	inline Const_Iterator begin() const
		{ return Const_Iterator(head.next, 0); }
	inline Const_Iterator end() const
		{ return Const_Iterator(&tail, _count); }

	inline Reverser rbegin()
		{ return Iterator(&tail, _count); }
	inline Reverser rend()
		{ return Iterator(head.next, 0); }
	inline Const_Reverser rbegin() const
		{ return Iterator(&tail, _count); }
	inline Const_Reverser rend() const
		{ return Iterator(head.next, 0); }

	void move(Linkedlist &t);	
	void swap(Linkedlist &t);

	void set(const T *p, size_t n)
		{ this->set<const T*>(p, n); }

	void clear();
	inline size_t count() const
		{ return _count; }

	T &operator [] (ssize_t i);
	const T &operator [] (ssize_t i) const;

	inline const T &first() const
		{ return this->operator [] (0); }
	inline const T &last() const
		{ return this->operator [] (-1); }
	
	void push(const T &val);
	T pop();

	void unshift(const T &val);
	T shift();

	void insert(ssize_t index, const T &val);
	Iterator insertAt(Iterator pos, const T &val);

	void remove(ssize_t index, size_t n);
	Iterator removeAt(Iterator pos, size_t n);
	
};	

template <typename T, typename Alloc>
class Linkedlist_Iterator {
	friend class Linkedlist<T, Alloc>;
protected:
	mutable Linkedlist_Node<T> *curr;
	mutable size_t index;
public:
	typedef T	value_t;

	Linkedlist_Iterator() : curr(), index() {}
	Linkedlist_Iterator(const Linkedlist_Iterator &i) : curr(i.curr), index(i.index) {}
	Linkedlist_Iterator(Linkedlist_Node<T> * const node, size_t i) :
		curr(node), index(i) {}

	inline const Linkedlist_Iterator &operator = (const Linkedlist_Iterator &t) const
		{ curr = t.curr; index = t.index; return *this; }

	inline T &operator * () { return curr->value; }
	inline const T &operator * () const { return curr->value; }
	inline T *operator -> () { return &curr->value; }
	inline const T *operator -> () const { return &curr->value; }
	const Linkedlist_Iterator &operator ++ () const {
		if (curr->next == 0) throw Erange();
		curr = curr->next;
		++index;
		return *this;
	}	
	const Linkedlist_Iterator &operator -- () const {
		if (curr->prev == 0) throw Erange();
		curr = curr->prev;
		--index;
		return *this;
	}
	Linkedlist_Iterator operator ++ (int) const {
		Linkedlist_Iterator tmp(*this);
		operator ++();
		return tmp;
	}
	Linkedlist_Iterator operator -- (int) const {
		Linkedlist_Iterator tmp(*this);
		operator --();
		return tmp;
	}
	inline ptrdiff_t operator - (const Linkedlist_Iterator &t)
		{ return index - t.index; }
	inline bool operator == (const Linkedlist_Iterator &i) const
		{ return curr == i.curr; }
	inline bool operator != (const Linkedlist_Iterator &i) const
		{ return curr != i.curr; }
	
};


#include "Linkedlist.tcc"

#endif
