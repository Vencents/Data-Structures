
template <typename Lst, typename Predicate>
Lst List::filter(const Lst &lst, Predicate pred) {
	Lst tmp;
	typename Const<typename Lst::Iterator>::type begin, end;
	begin = lst.begin(); end = lst.end();
	for (; begin != end; ++begin) {
		if (pred(*begin)) tmp.push(*begin);
	}
	return tmp;
}

template <typename Lst, typename Callback>
Lst List::map(const Lst &lst, Callback func) {
	Lst tmp;
	typename Const<typename Lst::Iterator>::type begin, end;
	begin = lst.begin(); end = lst.end();
	while (begin != end) tmp.push(func(*begin++));
	return tmp;
}

template <typename Lst>
typename Lst::value_t List::product(const Lst &lst) {
	typename Const<typename Lst::Iterator>::type begin, end;
	begin = lst.begin(); end = lst.end();
	if (begin == end) return typename Lst::value_t();
	typename Lst::value_t val(*begin++);
	while (begin != end) val *= *begin++;
	return val;
}

template <typename Lst, typename Callback>
typename Lst::value_t List::reduce(const Lst &lst, Callback func) {
	typename Lst::value_t result = typename Lst::value_t();
	typename Const<typename Lst::Iterator>::type begin, end;
	begin = lst.begin(); end = lst.end();
	while (begin != end) func(result, *begin++);
	return result;
}

template <typename Lst>
typename Lst::value_t List::sum(const Lst &lst) {
	typename Lst::value_t val = typename Lst::value_t();
	typename Const<typename Lst::Iterator>::type begin, end;
	begin = lst.begin(); end = lst.end();
	while (begin != end) val += *begin++;
	return val;
}
