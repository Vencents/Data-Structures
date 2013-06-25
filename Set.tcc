
template <typename T, typename Container>
template <typename InputIter>
void Set<T, Container>::set(typename Const<InputIter>::type p, size_t n) {
	c.clear();
	for (size_t i = 0; i < n; ++i, ++p) c.insert(*p);
}
template <typename T, typename Container>
void Set<T, Container>::set(typename Const<ptr_t>::type p, size_t n)
	{ this->set<ptr_t>(p, n); }

template <typename T, typename Container>
template <size_t N>
Set<T, Container>::Set(const value_t (&lst)[N]) : c()
	{ this->set<ptr_t>((ptr_t)lst, N); }
template <typename T, typename Container>
Set<T, Container>::Set(typename Const<ptr_t>::type p, size_t n) : c()
	{ this->set<ptr_t>(p, n); }
	
template <typename T, typename Container>
bool Set<T, Container>::exists(const Set &s) const {
	Iterator it, end = s.end();
	for (it = s.begin(); it != end; ++it)
		if (!c.exists(*it)) { return false; }
	return true;
}

template <typename T, typename Container>
void Set<T, Container>::insert(const Set &s) {
	Iterator it, end = s.end();
	for (it = s.begin(); it != end; ++it)
		c.insert(*it);
}

template <typename T, typename Container>
void Set<T, Container>::remove(const Set &s) {
	Iterator it, end = s.end();
	for (it = s.begin(); it != end; ++it) {
		try { c.remove(*it); } catch(Exception &e) {}
	}
}

