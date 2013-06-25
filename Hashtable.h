#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Hash.h"
#include "Pair.h"
#include "Types.h"
#include "Array.h"
#include "Allocator.h"

template <
	typename Key,
	typename Hashfunc,
	typename Alloc >
class Hashtable_Iterator;

template <
	typename Key,
	typename Hashfunc = Hash<Key>,
	typename Alloc = Allocator >
class Hashtable {
public:
	typedef Key			key_t;
	typedef Hashtable_Iterator<Key, Hashfunc, Alloc>	Iterator;
protected:
	typedef Array<key_t, Alloc>		bucket_t;
	typedef Array<bucket_t, Alloc>	table_t;	

	mutable table_t	table;
	Hashfunc		hasher;
	mutable size_t	_count;
	
	void rehash(size_t newtablesize);
public:
	Hashtable() : hasher(), _count(), table(9) {}
	Hashtable(const Hashtable &h) :
		table(h.table), _count(h._count), hasher() {}
	~Hashtable() {}

	void swap(Hashtable &h);
	void move(Hashtable &h);

	Iterator begin() const;
	Iterator end() const;
	
	void insert(const key_t &k);
	void remove(const key_t &k);
	bool exists(const key_t &k) const;
	const key_t *find(const key_t &k) const;

	void clear();
	inline size_t count() const
		{ return _count; }
};


template <typename Key, typename Hashfunc, typename Alloc>
class Hashtable_Iterator {
	friend class Hashtable<Key, Hashfunc, Alloc>;
public:
	typedef Key	key_t;
protected:
	typedef Array<key_t, Alloc>		bucket_t;
	typedef Array<bucket_t, Alloc>	table_t;

	mutable table_t *table;	
	mutable size_t tpos, bpos;
public:
	Hashtable_Iterator() : tpos(), bpos(), table() {}
	Hashtable_Iterator(table_t &tbl, size_t t, size_t b) :
		tpos(t), bpos(b), table(&tbl) {}
	Hashtable_Iterator(const Hashtable_Iterator &h) :
		tpos(h.tpos), bpos(h.bpos), table(h.table) {}
	
	Hashtable_Iterator &operator =(const Hashtable_Iterator &h)
		{ table=h.table; tpos=h.tpos; bpos=h.bpos; return *this; }

	const key_t &operator * () const
		{ return table->operator [](tpos)[bpos]; }
	const key_t *operator -> () const
		{ return &table->operator [](tpos)[bpos]; }

	const Hashtable_Iterator &operator ++ () const;
	const Hashtable_Iterator &operator -- () const;

	const Hashtable_Iterator operator ++ (int) const {
		Hashtable_Iterator tmp(*this);
		this->operator ++();
		return tmp;
	}
	const Hashtable_Iterator operator -- (int) const {
		Hashtable_Iterator tmp(*this);
		this->operator --();
		return tmp;
	}
	
	bool operator == (const Hashtable_Iterator &i) const
		{ return table==i.table && tpos==i.tpos && bpos==i.bpos; }
	bool operator != (const Hashtable_Iterator &i) const
		{ return bpos!=i.bpos || tpos!=i.tpos || table!=i.table; }
};

#include "Hashtable.tcc"

#endif
