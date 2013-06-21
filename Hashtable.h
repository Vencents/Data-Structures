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
	Val	value;

	Hashtable_Pair() : key(), value() {}
	Hashtable_Pair(const Hashtable_Pair &p) : key(p.key), value(p.value) {}
	~Hashtable_Pair() {}
	Hashtable_Pair &operator =(const Hashtable_Pair &p)
		{ key = p.key; value = p.value; return *this; }
};

template <typename Key, typename Val, typename Hashfunc = Hash<Key>, typename Alloc = Allocator>
class Hashtable {
public:
	typedef Key				key_t;
	typedef Val				value_t;
	typedef Hashtable_Pair<key_t, value_t>	pair_t;

protected:
	typedef Array<pair_t, Alloc>		bucket_t;
	typedef Array<bucket_t, Alloc>		table_t;
	
	table_t table;
	Hashfunc hasher;
	size_t _count;
	
	void rehash(size_t newtablesize);
public:
	Hashtable() : hasher(), _count(), table(4) {}
	~Hashtable() {}

	value_t &operator [] (const key_t &k);
	const value_t &operator [] (const key_t &k) const;
	
	void remove(const key_t &k);
	bool exists(const key_t &k);

	void clear();
	inline size_t count() { return _count; }
	
	
};

#include "Hashtable.tcc"

#endif
