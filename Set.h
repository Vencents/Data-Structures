#ifndef SET_H
#define SET_H

#include "Hashtable.h"

template <typename T>
class Set;

template <typename T>
class Set_Iterator {
	friend class Set<T>;
protected:
	mutable typename Hashtable<T, char>::Iterator it;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;

	Set_Iterator() : it() {}
	Set_Iterator(const Set_Iterator &i) : it(i.it) {}
	Set_Iterator(typename Const<typename Hashtable<T, char>::Iterator>::type i) : it(i) {}

	const Set_Iterator &operator =(const Set_Iterator &i) const { it = i.it; return *this; }
	
	value_t operator * () const { return it->key; }
	const ptr_t operator -> () const { return &it->key; }
	
	const Set_Iterator &operator ++ () const { ++it; return *this; }
	const Set_Iterator &operator -- () const { --it; return *this; }
	Set_Iterator operator ++ (int) const {
		Set_Iterator tmp(*this);
		++it;
		return tmp;
	}
	Set_Iterator operator -- (int) const {
		Set_Iterator tmp(*this);
		--it;
		return tmp;
	}
	bool operator == (const Set_Iterator &i) const
		{ return it == i.it; }
	bool operator != (const Set_Iterator &i) const
		{ return it != i.it; }		
};

template <typename T>
class Set {
protected:
	mutable Hashtable<T, char> c;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;
	typedef Set_Iterator<T>	Iterator;

	template <typename InputIter>
	void set(typename Const<InputIter>::type p, size_t n);
	void set(typename Const<ptr_t>::type p, size_t n);

	Set() : c() {}
	Set(const Set &s) : c(s.c) {}
	template <size_t N>
	Set(const value_t (&lst)[N]);
	Set(typename Const<ptr_t>::type p, size_t n);
		
	
	Set &operator = (const Set &s);

	Iterator begin();
	Iterator end(); 
	typename Const<Iterator>::type begin() const;
	typename Const<Iterator>::type end() const; 
		
	bool contains(typename Const<ref_t>::type val) const;
	bool contains(const Set &s) const;
	
	void insert(typename Const<ref_t>::type val);
	void insert(const Set &s);

	void remove(typename Const<ref_t>::type val);
	void remove(const Set &s);

	void retain(const Set &s);

	inline size_t count() const
		{ return c.count(); }
	inline void clear()
		{ c.clear(); }
	inline void move(Set &s)
		{ c.move(s.c); }
	inline void swap(Set &s)
		{ c.swap(s.c); }

};

#include "Set.tcc"	

#endif

