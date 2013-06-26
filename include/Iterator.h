#ifndef ITER_H
#define ITER_H
#include "Types.h"


template <typename _Iterator>
class Iterator_Traits {
public:
	typedef typename _Iterator::value_t	value_t;
	typedef typename _Iterator::ptr_t	ptr_t;
	typedef typename _Iterator::ref_t	ref_t;
};

template <typename T>
class Iterator_Traits<T*> {
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;
};

template <typename T>
class Iterator_Traits<const T*> {
public:
	typedef T	value_t;
	typedef const T	*ptr_t;
	typedef const T	&ref_t;
};

template <typename T, typename _ptr_t = T*, typename _ref_t = T&>
class Iterator {
public:
	typedef T	value_t;
	typedef _ptr_t	ptr_t;
	typedef _ref_t	ref_t;
};

template <typename _Iter>
class Reverser
: public Iterator <typename Iterator_Traits<_Iter>::value_t,
			typename Iterator_Traits<_Iter>::ptr_t,
			typename Iterator_Traits<_Iter>::ref_t>
{
protected:
	mutable _Iter it;
	typedef Iterator_Traits<_Iter> traits;
public:
	typedef typename traits::value_t	value_t;
	typedef typename traits::ptr_t		ptr_t;
	typedef typename traits::ref_t		ref_t;

	Reverser() : it() {}
	Reverser(_Iter i) : it(i) { }
	Reverser(const Reverser &r) : it(r.it) { }
	
	ref_t operator * () { _Iter tmp = it; return *--tmp; }
	const ref_t operator * () const { _Iter tmp = it; return *--tmp; }
	ptr_t operator -> () { return &(operator*()); }
	const ptr_t operator -> () const { return &(operator*()); }
	Reverser &operator ++ () const { --it; return *this; }
	Reverser &operator -- () const { ++it; return *this; }
	Reverser operator ++ (int) const {
		Reverser tmp = *this;
		--it;
		return tmp;
	}
	Reverser operator -- (int) const {
		Reverser tmp = *this;
		++it;
		return tmp;
	}
	Reverser operator + (ptrdiff_t n) const {
		return Reverser(it - n);
	}
	Reverser operator - (ptrdiff_t n) const {
		return Reverser(it + n);
	}
	Reverser &operator += (ptrdiff_t n) const {
		it -= n; return *this;
	}
	Reverser &operator -= (ptrdiff_t n) const {
		it += n; return *this;
	}
	ref_t	operator [] (ptrdiff_t n) {
		return *(*this + n);
	}
	const ref_t operator [] (ptrdiff_t n) const {
		return *(*this + n);
	}
	
	bool operator == (const Reverser &r) const { return it == r.it; }
	bool operator != (const Reverser &r) const { return it != r.it; }
	bool operator > (const Reverser &r) const { return it > r.it; }
	bool operator < (const Reverser &r) const { return it < r.it; }
	bool operator >= (const Reverser &r) const { return it >= r.it; }
	bool operator <= (const Reverser &r) const { return it <= r.it; }
};

template <typename Container>
class Pusher
: public Iterator<typename Container::value_t,
			typename Container::ptr_t,
			typename Container::ref_t> {
protected:
	Container *c;
public:
	Pusher() : c() {}
	Pusher(Container &i) : c(&i) {}
	Pusher(const Pusher &p) : c(p.c) {}

	Pusher &operator * () { return *this; }
	Pusher &operator ++ () { return *this; }
	Pusher &operator ++ (int) { return *this; }
	Pusher &operator = (typename Const<typename Container::ref_t>::type val) {	
		c->push(val); return *this; 	
	}	
};

template <typename Container>
class Unshifter
: public Iterator<typename Container::value_t,
			typename Container::ptr_t,
			typename Container::ref_t> {
protected:
	Container *c;
public:
	Unshifter() : c() {}
	Unshifter(Container &i) : c(&i) {}
	Unshifter(const Unshifter &s) : c(s.c) {}
	
	Unshifter &operator * () { return *this; }
	Unshifter &operator ++ () { return *this; }
	Unshifter &operator ++ (int) { return *this; }
	Unshifter &operator = (typename Const<typename Container::ref_t>::type val) {
		c->unshift(val); return *this;
	}
};


#endif	
