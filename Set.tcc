
template <typename T>
template <typename InputIter>
void Set<T>::set(typename Const<InputIter>::type p, size_t n) {
	c.clear();
	for (size_t i = 0; i < n; ++i, ++p) c[*p];
}
template <typename T>
void Set<T>::set(typename Const<ptr_t>::type p, size_t n)
	{ this->set<ptr_t>(p, n); }

template <typename T>
template <size_t N>
Set<T>::Set(const value_t (&lst)[N]) : c()
	{ this->set<ptr_t>((ptr_t)lst, N); }
template <typename T>
Set<T>::Set(typename Const<ptr_t>::type p, size_t n) : c()
	{ this->set<ptr_t>(p, n); }
	
template <typename T>
Set<T> &Set<T>::operator = (const Set &s)
	{ c = s.c; return *this; }

template <typename T>
typename Set<T>::Iterator Set<T>::begin()
	{ return Iterator(c.begin()); }
template <typename T>
typename Set<T>::Iterator Set<T>::end()
	{ return Iterator(c.end()); }
template <typename T>
typename Const<typename Set<T>::Iterator>::type Set<T>::begin() const
	{ return Iterator(c.begin()); }
template <typename T>
typename Const<typename Set<T>::Iterator>::type Set<T>::end() const
	{ return Iterator(c.end()); }

template <typename T>	
bool Set<T>::contains(typename Const<ref_t>::type val) const
	{ return c.contains(val); }
template <typename T>
bool Set<T>::contains(const Set &s) const {
	Iterator it, end = s.end();
	for (it = s.begin(); it != end; ++it)
		if (!c.contains(it.it->key)) { return false; }
	return true;
}

template <typename T>
void Set<T>::insert(typename Const<ref_t>::type val)
	{ c[val]; }
template <typename T>
void Set<T>::insert(const Set &s) {
	Iterator it, end = s.end();
	for (it = s.begin(); it != end; ++it)
		c[it.it->key];
}

template <typename T>
void Set<T>::remove(typename Const<ref_t>::type val)
	{ c.remove(val); }
template <typename T>
void Set<T>::remove(const Set &s) {
	Iterator it, end = s.end();
	for (it = s.begin(); it != end; ++it) {
		try { c.remove(it.it->key); } catch(Exception &e) {}
	}
}

template <typename T>
void Set<T>::retain(const Set &s) {
	Iterator it(c.begin()), end(c.end());
	while (it != end) {
		if (!s.contains(it.it->key))
			it.it = c.remove(it.it);
		else ++it;
	}
}

