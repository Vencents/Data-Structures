
template <typename T>	
template <typename InputIter>
void Multiset<T>::set(typename Const<InputIter>::type p, size_t n) {
	_count = 0;
	c.clear();
	for (size_t i = 0; i < n; ++i, ++p) {
		++c[*p];
		++_count;
	}
}

template <typename T>
void Multiset<T>::set(typename Const<ptr_t>::type p, size_t n)
	{ this->set<ptr_t>(p, n); }

template <typename T>
template <size_t N>
Multiset<T>::Multiset(const value_t (&lst)[N]) : c(), _count()
	{ this->set<ptr_t>((ptr_t)lst, N); }
template <typename T>
Multiset<T>::Multiset(typename Const<ptr_t>::type p, size_t n) : c(), _count()
	{ this->set<ptr_t>(p, n); }

template <typename T>
Multiset<T> &Multiset<T>::operator =(const Multiset &m)
	{ c = m.c; _count = m._count; return *this; }

template <typename T>
typename Multiset<T>::Iterator Multiset<T>::begin()
	{ return Iterator(c.begin(), 0); }
template <typename T>
typename Multiset<T>::Iterator Multiset<T>::end()
	{ return Iterator(c.end(), 0); }
template <typename T>
typename Const<typename Multiset<T>::Iterator>::type Multiset<T>::begin() const
	{ return Iterator(c.begin(), 0); }
template <typename T>
typename Const<typename Multiset<T>::Iterator>::type Multiset<T>::end() const
	{ return Iterator(c.end(), 0); }

template <typename T>
bool Multiset<T>::contains(typename Const<ref_t>::type val)
	{ return c.contains(val); }
template <typename T>
bool Multiset<T>::contains(const Multiset &m) {
	typename Hashtable<T, size_t>::Iterator it(m.c.begin()), end(m.c.end());
	for (; it != end; ++it) {
		if (c.contains(it->key)) {
			if (it->value != c[it->key]) return false;
		} else return false;
	}
	return true;
}

template <typename T>
size_t Multiset<T>::countof(typename Const<ref_t>::type val)
	{ return c[val]; }
template <typename T>
void Multiset<T>::scale(size_t n) {
	typename Hashtable<T, size_t>::Iterator it(c.begin()), end(c.end());
	for (; it != end; ++it) {
		_count -= it->value;
		it->value *= n;
		_count += it->value;
	}
}	

template <typename T>
void Multiset<T>::insert(typename Const<ref_t>::type val)
	{ ++c[val]; ++_count; }
template <typename T>
void Multiset<T>::insert(typename Const<ref_t>::type val, size_t n)
	{ c[val] += n; _count += n; }
template <typename T>
void Multiset<T>::insert(const Multiset &m) {
	typename Hashtable<T, size_t>::Iterator it(m.c.begin()), end(m.c.end());
	for (; it != end; ++it) {
		c[it->key] += it->value;
	}
}

template <typename T>
void Multiset<T>::remove(typename Const<ref_t>::type val) {
	if (c.contains(val) == false) throw Erange();
	size_t &v = c[val];
	if (--v == 0) c.remove(val);
}
template <typename T>
void Multiset<T>::remove(typename Const<ref_t>::type val, size_t n) {
	if (c.contains(val) == false) throw Erange();
	size_t *i = &c[val];
	if (*i < n) *i = 0;
	else *i -= n;	
}
template <typename T>
void Multiset<T>::remove(const Multiset &m) {
	size_t *n;
	typename Hashtable<T, size_t>::Iterator it(m.c.begin()), end(m.c.end());
	for (; it != end; ++it) {
		if (c.contains(it->key)) {
			n = &c[it->key];
			if (it->value >= *n) {
				_count -= *n;
				c.remove(it->key);
			} else {
				_count -= it->value;
				*n -= it->value;
			}	
		}
	}
}

template <typename T>
void Multiset<T>::retain(const Multiset &m) {
	size_t *i;
	typename Hashtable<T, size_t>::Iterator it(m.c.begin()), end(m.c.end());
	for (; it != end; ++it) {
		if (!c.contains(it->key)) c.remove(it->key);
		else {
			i = &c[it->key];
			if (*i > it->value) *i = it->value;
		}
	}
}

