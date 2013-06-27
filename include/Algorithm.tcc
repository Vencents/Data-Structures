	
	template <typename InputIter, typename T, typename Size>
	InputIter Algorithm::find(InputIter begin, const T &val, Size n) {
		Size i = Size();
		for (; i < n; ++i) {
			if (*begin == val) return begin;
			++begin;
		}
		return InputIter();
	}

	template <typename BidirectionalIter, typename T, typename Size>
	BidirectionalIter Algorithm::rfind(BidirectionalIter end, const T &val, Size n) {
		Size i = Size();
		for (; i < n; ++i) {
			if (*end == val) return end;
			--end;
		}
		return BidirectionalIter();
	}

	template <typename InputIter, typename Size>
	InputIter Algorithm::compare(InputIter s1, InputIter s2, Size n) {
		Size i = Size();
		for (; i != n; ++i, ++s1, ++s2) {
			if (*s1 != *s2) return s1;
		}
		return InputIter();
	}

	template <typename InputIter, typename Size>
	InputIter Algorithm::find(InputIter haystack, Size haystacklen, InputIter needle, Size needlelen) {
		Size end_index, i = Size();
		if (haystacklen == Size() || needlelen == Size()) return InputIter();
		if (needlelen > haystacklen) return InputIter();
		end_index = haystacklen - needlelen;
		for (; i <= end_index; ++i, ++haystack) {
			if (*haystack == *needle && compare(haystack, needle, needlelen) == InputIter())
				return haystack;
		}
		return  InputIter();
	}

	template <typename BidirectionalIter, typename InputIter, typename Size>
	BidirectionalIter Algorithm::rfind(BidirectionalIter haystackend, Size haystacklen, InputIter needle, Size needlelen) {
		Size end_index, i = Size();
		if (haystacklen == Size() || needlelen == Size()) return BidirectionalIter();
		if (needlelen > haystacklen) return BidirectionalIter();
		end_index = haystacklen - needlelen;
		for (; i <= end_index; ++i, --haystackend) {
			if (*haystackend == *needle && compare(haystackend, needle, needlelen))
				return haystackend;
		}
		return BidirectionalIter();
	}

	template <typename InputIter, typename T>
	InputIter Algorithm::find(InputIter it, const T &val) {
		while (*it != val) ++it;
		return it;
	}

	template <typename BidirectionalIter, typename T>
	BidirectionalIter Algorithm::rfind(BidirectionalIter it, const T &val) {
		while (*it != val) --it;
		return it;
	}

	template <typename InputIter, typename OutputIter, typename Size>
	OutputIter Algorithm::copy(OutputIter it, InputIter src, Size n) {
		Size i = Size();
		OutputIter a = it;
		for (; i != n; ++i, ++a, ++src) *a = *src;
		return it;
	}

	template <typename T>
	void Algorithm::swap(T &a, T &b) {
		T tmp;
		tmp = a;
		a = b;
		b = tmp;
	}

	template <typename InputIter, typename OutputIter, typename Size>
	OutputIter Algorithm::move(OutputIter dst, InputIter src, Size n) {
		Size i = Size();
		InputIter begin = src;
		OutputIter end = dst;
		for (; i != n; ++i) {
			if (src == end) src = begin;
			swap(*src++, *dst++);
		}
	}

	template <typename OutputIter, typename T, typename Size>
	OutputIter Algorithm::fill(OutputIter dst, const T &val, Size n) {
		Size i = Size();
		OutputIter it = dst;
		for (; i != n; ++i) *it++ = val;
		return dst;
	}

	template <typename BidirectionalIter>
	void Algorithm::reverse(BidirectionalIter first, BidirectionalIter last) {
		while ((first != last) && (first != --last)) {
			swap(*first, *last);
			++first;
		}
	}

	template <typename InputIter, typename T>
	size_t Algorithm::count(InputIter it, const T &val) {
		size_t i = 0; 
		for (; *it++ != val; ++i);
		return i;
	}

	template <typename InputIter, typename T, typename Size>
	Size Algorithm::countof(InputIter it, Size n, const T &val) {
		Size i, j = Size();
		for (i = Size(); i < n; ++i) {
			if (*it++ == val) ++j;
		}
		return j;
	}

template <typename Lst, typename Predicate>
Lst Algorithm::List::filter(const Lst &lst, Predicate pred) {
	Lst tmp;
	typename Const<typename Lst::Iterator>::type begin, end;
	begin = lst.begin(); end = lst.end();
	for (; begin != end; ++begin) {
		if (pred(*begin)) tmp.push(*begin);
	}
	return tmp;
}

template <typename Lst, typename Callback>
Lst Algorithm::List::map(const Lst &lst, Callback func) {
	Lst tmp;
	typename Const<typename Lst::Iterator>::type begin, end;
	begin = lst.begin(); end = lst.end();
	while (begin != end) tmp.push(func(*begin++));
	return tmp;
}

template <typename Lst>
typename Lst::value_t Algorithm::List::product(const Lst &lst) {
	typename Const<typename Lst::Iterator>::type begin, end;
	begin = lst.begin(); end = lst.end();
	if (begin == end) return typename Lst::value_t();
	typename Lst::value_t val(*begin++);
	for (; begin != end; ++begin) val *= *begin;
	return val;
}

template <typename Lst, typename Callback>
typename Lst::value_t Algorithm::List::reduce(const Lst &lst, Callback func) {
	typename Lst::value_t result = typename Lst::value_t();
	typename Const<typename Lst::Iterator>::type begin, end;
	begin = lst.begin(); end = lst.end();
	for (; begin != end; ++begin) func(result, *begin);
	return result;
}

template <typename Lst>
typename Lst::value_t Algorithm::List::sum(const Lst &lst) {
	typename Lst::value_t val = typename Lst::value_t();
	typename Const<typename Lst::Iterator>::type begin, end;
	begin = lst.begin(); end = lst.end();
	for (; begin != end; ++begin) val += *begin;
	return val;
}
