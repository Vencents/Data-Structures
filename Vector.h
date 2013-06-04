#ifndef VECTOR_H
#define VECTOR_H

#include "Types.h"
#include <math.h>
#include <stdarg.h>

template <size_t N = 3, typename T = float>
class Vector {
public:
	typedef T		value_t;
	typedef T		*ptr_t;
	typedef T		&ref_t;
protected:
	value_t a[N];
public:
	Vector() {}
	Vector(const Vector &v) : a(v.a) {}
	Vector(typename Const<ref_t>::type r, ...);
	Vector operator - (const Vector &v) const;
	Vector operator + (const Vector &v) const;
	Vector &operator = (const Vector &v);
	Vector operator * (typename Const<ref_t>::type r) const;
	Vector &operator -= (const Vector &v);
	Vector &operator += (const Vector &v);
	Vector &operator *= (typename Const<ref_t>::type r);
	Vector operator ~ () const;
	void Assign(typename Const<ref_t>::type r, ...);
	void Clear();
	value_t DotProduct(const Vector &v) const;
	void Snap();
	void Normalize();
	value_t Length() const;
	value_t LengthSquared() const; 
	inline ref_t operator [] (size_t index) { return a[index]; }
	inline typename Const<ref_t>::type operator [] (ssize_t index) const { return a[index]; }
	bool operator == (const Vector &v) const;
	bool operator != (const Vector &v) const;
};

#include "Vector.tcc"

#endif

