#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Types.h"
#include "Exception.h"

inline void *operator new(size_t, void *p) throw() { return p; }

template <typename T>
class Allocator_Traits {
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;
};

template <typename T, typename Traits = Allocator_Traits<T> >
class Allocator_Base {
public:
	typedef typename Traits::value_t	value_t;
	typedef typename Traits::ptr_t		ptr_t;
	typedef typename Traits::ref_t		ref_t;

	virtual ptr_t	alloc(size_t) = 0;
	virtual ptr_t	realloc(ptr_t, size_t) = 0;
	virtual void	free(ptr_t) = 0;
	
	static inline void construct(ptr_t p, typename Const<ref_t>::type t)
		{ new ((void*)p)value_t(t); }
	static inline void destroy(ptr_t p)
		{ ((value_t*)p)->~value_t(); }
	static inline void reconstruct(ptr_t p, typename Const<ref_t>::type t)
		{ destroy(p); construct(p, t); }

	static inline void construct(ptr_t p, typename Const<ref_t>::type t, size_t n)
		{ for (size_t i = 0; i < n; ++i, ++p) construct(p, t); }
	static inline void destroy(ptr_t p, size_t n)
		{ for (size_t i = 0; i < n; ++i, ++p) destroy(p); }
	static inline void reconstruct(ptr_t p, typename Const<ref_t>::type t, size_t n)
		{ for (size_t i = 0; i < n; ++i, ++p) reconstruct(p, t); }
};	
	
template <typename T>
class Allocator : public Allocator_Base<T> {
public:
	typedef typename Allocator_Base<T>::value_t	value_t;
	typedef typename Allocator_Base<T>::ptr_t	ptr_t;
	typedef typename Allocator_Base<T>::ref_t	ref_t;

	ptr_t	alloc(size_t n) {
		ptr_t p = (ptr_t)::malloc(n * sizeof(value_t));
		if (p == ptr_t()) throw Enomem();
		return p;
	}

	ptr_t	realloc(ptr_t p, size_t n) {
		ptr_t ptr = (ptr_t)::realloc(p, n * sizeof(value_t));
		if (ptr == ptr_t()) throw Enomem();
		return ptr;
	}

	void	free(ptr_t p) {
		::free(p);
	}
};

#endif 
