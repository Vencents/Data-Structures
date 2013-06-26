#ifndef HASH_H 
#define HASH_H

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

#endif
