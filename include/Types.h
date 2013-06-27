#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <wchar.h>
#include <stdarg.h>

/*
 * Property declaration in classes, example:
 * Property(int) count {
 *	Get { return foo.bar(); }
 *	Set { baz = new_value; }
 * }
 */
//#define Property(T) class { private: typedef T value_t; T value; public: void _()  
//#define Get } operator value_t () 
//#define Set void operator = (const value_t &new_value)

#ifdef _WIN32
typedef signed long int ssize_t;
#endif
 
template <typename T>
struct Unreference { typedef T type; };

template <typename T>
struct Unreference<T&> { typedef T type; };

template <typename T>
struct Unconst { typedef T type; };

template <typename T>
struct Unconst<const T> { typedef T type; };

template <typename T>
struct Unpointer { typedef T type; };

template <typename T>
struct Unpointer<T*> { typedef T type; };

template <typename T>
struct Unvolatile { typedef T type; };

template <typename T>
struct Unvolatile<volatile T> { typedef T type; };

template <typename T>
struct Const { typedef const T type; };

template <typename T>
struct Const<T*> { typedef const T *type; };

template <typename T>
struct Const<T&> { typedef const T &type; };

template <typename T>
struct Pointer { typedef typename Unreference<T>::type type; };

template <typename T>
struct Reference { typedef T &type; };

template <typename T>
struct Volatile { typedef volatile T type; };


#endif
