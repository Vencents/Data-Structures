#ifndef HASHTABLE_H 
#define HASHTABLE_H 

#include "Types.h"
#include "Array.h"
#include "Allocator.h"

#define _default_hash(key, size)				\
	size_t hash = 2166136261UL, len = size;			\
	const char *cptr = reinterpret_cast<const char*>(&key);	\
	for (; len; --len) hash = (hash * 131) + *cptr++;	\
	return hash;						\

template <typename Key>
class Hash {
public:
	typedef Key	key_t;
	size_t operator ()(const key_t &k) const 
		{ _default_hash(k, sizeof(k)); }
};

#define _specialize_decimal_hash(T)						\
template <>									\
class Hash<T> {									\
public:										\
	typedef T	key_t;							\
	size_t operator () (key_t k)						\
		{ if (k == 0.0) return 0; _default_hash(k, sizeof(k)); }	\
};

_specialize_decimal_hash(float);
_specialize_decimal_hash(double);
_specialize_decimal_hash(long double);

#undef _specialize_decimal_hash

template <typename Key>
class Hash<Key*> {
public:
	typedef Key key_t;
	size_t operator ()(key_t *k) const
		{ return reinterpret_cast<size_t>(k); }
};

#define _specialize_integer_hash(T)				\
	template <>						\
	class Hash<T> {						\
	public:							\
		typedef T	key_t;				\
		size_t operator ()(key_t k) const 		\
			{ return static_cast<size_t>(k); }	\
	};

_specialize_integer_hash(bool)
_specialize_integer_hash(char)
_specialize_integer_hash(signed char)
_specialize_integer_hash(unsigned char)
_specialize_integer_hash(wchar_t)
_specialize_integer_hash(short)
_specialize_integer_hash(int)
_specialize_integer_hash(long)
_specialize_integer_hash(long long)
_specialize_integer_hash(unsigned short)
_specialize_integer_hash(unsigned int)
_specialize_integer_hash(unsigned long)
_specialize_integer_hash(unsigned long long)

#undef _specialize_integer_hash

template <typename Key, typename Val>
class Hashtable_Pair {
public:
	Key	key;
	Val		value;

	Hashtable_Pair() : key(), value() {}
	Hashtable_Pair(const Key &k) : key(k), value() {}
	Hashtable_Pair(const Hashtable_Pair &p) : key(p.key), value(p.value) {}
	~Hashtable_Pair() {}
	Hashtable_Pair &operator =(const Hashtable_Pair &p)
		{ key = p.key; value = p.value; return *this; }
	
};

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
class Hashtable;

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
class Hashtable_Iterator {
	friend class Hashtable<Key, Val, Hashfunc, Alloc>;
public:
	typedef Key				key_t;
	typedef Val				value_t;
	typedef Hashtable_Pair<key_t, value_t>	pair_t;
protected:
	typedef Array<pair_t, Alloc>		bucket_t;
	typedef Array<bucket_t, Alloc>		table_t;
	
	mutable table_t *table;
	mutable size_t tpos, bpos;
public:
	Hashtable_Iterator() : tpos(), bpos(), table() {}
	Hashtable_Iterator(table_t &tbl, size_t t, size_t b) : tpos(t), bpos(b), table(&tbl) {}
	Hashtable_Iterator(const Hashtable_Iterator &h) : tpos(h.tpos), bpos(h.bpos), table(h.table) {}

	Hashtable_Iterator &operator =(const Hashtable_Iterator &h) {
		table = h.table; tpos = h.tpos; bpos = h.bpos;
		return *this;
	}
	
	pair_t &operator * () { return table->operator [](tpos)[bpos]; }
	const pair_t &operator * () const { return table->operator [](tpos)[bpos]; }	
	
	pair_t *operator -> () { return &table->operator [](tpos)[bpos]; }
	const pair_t *operator -> () const { return &table->operator [](tpos)[bpos]; }
	
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

	bool operator == (const Hashtable_Iterator &i) const {
		return table == i.table && tpos == i.tpos && bpos == i.bpos;
	}

	bool operator != (const Hashtable_Iterator &i) const {
		return bpos != i.bpos || tpos != i.tpos || table != i.table;
	}

};


template <typename Key, typename Val, typename Hashfunc = Hash<Key>, typename Alloc = Allocator>
class Hashtable {
public:
	typedef Key				key_t;
	typedef Val				value_t;
	typedef Hashtable_Pair<Key, Val>	pair_t;
	typedef Hashtable_Iterator<Key, Val, Hashfunc, Alloc>	Iterator;
	typedef	value_t				&ref_value_t;
protected:
	typedef Array<pair_t, Alloc>		bucket_t;
	typedef Array<bucket_t, Alloc>		table_t;

	table_t table;
	Hashfunc hasher;
	size_t _count;
	
	void rehash(size_t newtablesize);
public:
	Hashtable() : hasher(), _count(), table(9) {}
	Hashtable(const Hashtable &h);
	~Hashtable() {}

	Hashtable &operator =(const Hashtable &t)
		{ table = t.table; _count = t._count; }

	value_t &operator [] (const key_t &k);
	typename Const<ref_value_t>::type operator [] (const key_t &k) const;
	
	void remove(const key_t &k);
	bool contains(const key_t &k) const;

	void clear();
	inline size_t count() const { return _count; }

	void move(Hashtable &h);
	void swap(Hashtable &h);

	Iterator begin();
	Iterator end();
	typename Const<Iterator>::type begin() const;
	typename Const<Iterator>::type end() const;

	Iterator remove(Iterator pos, size_t n = 1);
	
	Iterator from(const key_t &k);
	typename Const<Iterator>::type from(const key_t &k) const;

};

#include "Hashtable.tcc"

#endif
