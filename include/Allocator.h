#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Types.h"
#include "Exception.h"

inline void *operator new(size_t, void *p) throw() { return p; }

class Allocator {
public:
	virtual void *alloc(size_t n)
		{ return ::malloc(n); }
	virtual void *realloc(void* p, size_t n)
		{ return ::realloc(p, n); }
	virtual void free(void* p)
		{ ::free(p); }
};

template <typename T, typename Alloc = Allocator>
class Object_Allocator {
protected:
	Alloc allocator;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;
 
	Object_Allocator() : allocator() {}
	
	ptr_t alloc(size_t n) {
		ptr_t p = (ptr_t)allocator.alloc(n * sizeof(value_t));
		if (p == NULL) throw Enomem();
		return p;
	}

	ptr_t realloc(ptr_t ptr, size_t n) {
		ptr_t p = (ptr_t)allocator.realloc(ptr, n * sizeof(value_t));
		if (p == NULL) throw Enomem();
		return p;
	}

	void free(ptr_t p) {
		allocator.free(p);
	}

	static inline void construct(ptr_t p)
		{ new ((void*)p)value_t(); }		
	static inline void construct(ptr_t p, typename Const<ref_t>::type t)
		{ new ((void*)p)value_t(t); }
	static inline void destroy(ptr_t p)
		{ ((value_t*)p)->~value_t(); }

	static inline void construct_range(ptr_t p, size_t n)
		{ for (size_t i = 0; i < n; ++i, ++p) construct(p); }
	static inline void construct_range(ptr_t p, typename Const<ref_t>::type t, size_t n)
		{ for (size_t i = 0; i < n; ++i, ++p) construct(p, t); }
	static inline void destroy_range(ptr_t p, size_t n)
		{ for (size_t i = 0; i < n; ++i, ++p) destroy(p); }
};

#endif 
