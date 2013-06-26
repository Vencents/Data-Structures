template <typename T, typename Container>
Multiset<T, Container>::Multiset(const Container &_c) : c(_c), _count() {
	Iterator it, end;
	end = c.end();
	for (it = c.begin(); it != end; ++it) {
		_count += it->count;
	}
}

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
	node_t n(key);
	const node_t *p;
	p = c.find(n);
	if (p) ++p->count;
	else c.insert(n);
	++_count;
}

template <typename T, typename Container>
void Multiset<T, Container>::insert(const value_t &key, size_t n) {
	Multiset_Node<T> node(key, n);
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

