
template <typename T, typename Container>	
template <typename InputIter>
void Multiset<T, Container>::set(typename Const<InputIter>::type p, size_t n) {
	_count = 0;
	c.clear();
	for (size_t i = 0; i < n; ++i, ++p) {
		c.insert(*p);
		++_count;
	}
}

template <typename T, typename Container>
void Multiset<T, Container>::set(typename Const<ptr_t>::type p, size_t n)
	{ this->set<ptr_t>(p, n); }

template <typename T, typename Container>
template <size_t N>
Multiset<T, Container>::Multiset(const value_t (&lst)[N]) : c(), _count()
	{ this->set<ptr_t>((ptr_t)lst, N); }
template <typename T, typename Container>
Multiset<T, Container>::Multiset(typename Const<ptr_t>::type p, size_t n) : c(), _count()
	{ this->set<ptr_t>(p, n); }

template <typename T, typename Container>
Multiset<T, Container> &Multiset<T, Container>::operator =(const Multiset &m)
	{ c = m.c; _count = m._count; return *this; }

template <typename T, typename Container>
bool Multiset<T, Container>::exists(const Multiset &m) {
	const node_t *p;
	typename Container::Iterator it(m.c.begin()), end(m.c.end());
	for (; it != end; ++it) {
		p = c.find(*it);
		if (p == 0) return false;
		if (it->count != p->count) return false;
	}
	return true;
}

template <typename T, typename Container>
size_t Multiset<T, Container>::countof(const value_t &key) {
	const node_t *p;
	p = c.find(key);
	if (p == 0) return 0;
	return p->count;
}

template <typename T, typename Container>
void Multiset<T, Container>::scale(size_t n) {
	typename Container::Iterator it(c.begin()), end(c.end());
	for (; it != end; ++it) {
		_count -= it->count;
		it->count *= n;
		_count += it->count;
	}
}	

template <typename T, typename Container>
void Multiset<T, Container>::insert(const value_t &key) {
	Multiset_Node<T> n(key);
	const node_t *p;
	p = c.find(n);
	if (p) ++p->count;
	else c.insert(n);
	++_count;
}

template <typename T, typename Container>
void Multiset<T, Container>::insert(const value_t &key, size_t n) {
	Multiset_Node<T> node(key);
	const node_t *p;
	p = c.find(node);
	if (p) p->count += n;
	else c.insert(node);
	_count += n;
}

template <typename T, typename Container>
void Multiset<T, Container>::insert(const Multiset &m) {
	const node_t *p;
	typename Container::Iterator it(m.c.begin()), end(m.c.end());
	for (; it != end; ++it) {
		this->insert(it->key, it->count);	
	}
}

template <typename T, typename Container>
void Multiset<T, Container>::remove(const value_t &key) {
	const node_t *p;
	p = c.find(key);
	if (p == 0) throw Erange();
	if (--p->count == 0) c.remove(key);
}
template <typename T, typename Container>
void Multiset<T, Container>::remove(const value_t &key, size_t n) {
	const node_t *p;
	p = c.find(key);
	if (p == 0) throw Erange();
	if (p->count <= n) c.remove(key);
	else p->count -= n;
}
template <typename T, typename Container>
void Multiset<T, Container>::remove(const Multiset &m) {
	typename Container::Iterator it(m.c.begin()), end(m.c.end());
	for (; it != end; ++it) {
		try { this->remove(it->key); } catch (Exception &ex) {}
	}
}

