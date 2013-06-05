#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdlib.h>

class Algorithm {
public:
	
	template <typename InputIter, typename T, typename Size>
	static InputIter find(InputIter begin, const T &val, Size n);

	template <typename BidirectionalIter, typename T, typename Size>
	static BidirectionalIter rfind(BidirectionalIter end, const T &val, Size n);

	template <typename InputIter, typename Size>
	static InputIter compare(InputIter s1, InputIter s2, Size n);
	
	template <typename InputIter, typename Size>
	static InputIter find(InputIter haystack, Size haystacklen, InputIter needle, Size needlelen);

	template <typename BidirectionalIter, typename InputIter, typename Size>
	static BidirectionalIter rfind(BidirectionalIter haystackend, Size haystacklen, InputIter needle, Size needlelen);

	template <typename InputIter, typename T>
	static InputIter find(InputIter begin, const T &val);

	template <typename BidirectionalIter, typename T>
	static BidirectionalIter rfind(BidirectionalIter end, const T &val);

	template <typename InputIter, typename OutputIter, typename Size>
	static OutputIter copy(OutputIter begin, InputIter src, Size n);

	template <typename T>
	static inline void swap(T &a, T &b);

	template <typename InputIter, typename OutputIter, typename Size>
	static OutputIter move(OutputIter dst, InputIter src, Size n);

	template <typename OutputIter, typename T, typename Size>
	static OutputIter fill(OutputIter dst, const T &val, Size n);

	template <typename BidirectionalIter>
	static void reverse(BidirectionalIter first, BidirectionalIter last);

	template <typename InputIter, typename T>
	static size_t count(InputIter it, const T &val);

	template <typename InputIter, typename T, typename Size>
	static Size countof(InputIter it, Size n, const T &val);	

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

};


#include "Algorithm.tcc"

#endif

