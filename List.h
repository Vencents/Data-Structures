#ifndef LIST_H
#define LIST_H

#include "Types.h"

class List {
public:	
	template <typename Lst, typename Predicate>
	static Lst filter(const Lst &lst, Predicate pred);

	template <typename Lst, typename Callback>
	static Lst map(const Lst &lst, Callback func);

	template <typename Lst>
	static typename Lst::value_t product(const Lst &lst);

	template <typename Lst, typename Callback>
	static typename Lst::value_t reduce(const Lst &lst, Callback func);

	template <typename Lst>
	static typename Lst::value_t sum(const Lst &lst);

	
};

#include "List.tcc"

#endif
