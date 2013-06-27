#ifndef ITER_H
#define ITER_H
#include "Types.h"

template <typename _Iter>
class Reverser {
protected:
	mutable _Iter it;
public:
	typedef typename _Iter::value_t	value_t;

	Reverser() : it() {}
	Reverser(_Iter i) : it(i) { }
	Reverser(const Reverser &r) : it(r.it) { }

	//operator _Iter () { return it; }
	
	value_t &operator * () { _Iter tmp = it; return *--tmp; }
	const value_t &operator * () const { _Iter tmp = it; return *--tmp; }
	value_t *operator -> () { return &(operator*()); }
	const value_t *operator -> () const { return &(operator*()); }
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
	value_t &operator [] (ptrdiff_t n) {
		return *(*this + n);
	}
	const value_t &operator [] (ptrdiff_t n) const {
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
class Pusher {
protected:
	Container *c;
public:
	typedef typename Container::value_t value_t;
	Pusher() : c() {}
	Pusher(Container &i) : c(&i) {}
	Pusher(const Pusher &p) : c(p.c) {}

	Pusher &operator * () { return *this; }
	Pusher &operator ++ () { return *this; }
	Pusher &operator ++ (int) { return *this; }
	Pusher &operator = (const value_t &val) {	
		c->push(val); return *this; 	
	}	
};

template <typename Container>
class Unshifter {
protected:
	Container *c;
public:
	typedef typename Container::value_t	value_t;
	Unshifter() : c() {}
	Unshifter(Container &i) : c(&i) {}
	Unshifter(const Unshifter &s) : c(s.c) {}
	
	Unshifter &operator * () { return *this; }
	Unshifter &operator ++ () { return *this; }
	Unshifter &operator ++ (int) { return *this; }
	Unshifter &operator = (const value_t &val) {
		c->unshift(val); return *this;
	}
};


#endif	
